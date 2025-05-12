#include <Input.h>
#include <Gyro.h>


void Gyro::setup() {
    if (!bno.begin()) {
        Serial.println("BNO055 not detected.");
        while (1);  //センサー未検出時は停止
    }
    bno.setExtCrystalUse(true);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(1000);
    quatyaw = gyro.get_yawfromquat(bno.getQuat());
    cordlastupdatetime = millis();
    yawlastupdatetime = millis();

    // カルマンフィルタ初期化
    transition_matrix(0,0) = 1;
    transition_matrix(0,1) = 0.01;
    transition_matrix(1,0) = 0;
    transition_matrix(1,1) = 1;

    observation_matrix(0,0) = 1;
    observation_matrix(0,1) = 0;

    process_noise(0,0) = 0.0001;
    process_noise(0,1) = 0;
    process_noise(1,0) = 0;
    process_noise(1,1) = 0.0001;

    observation_noise(0,0) = 0.01;

    state_vector(0) = 0;
    state_vector(1) = 0;

    error_covariance(0,0) = 1;
    error_covariance(0,1) = 0;
    error_covariance(1,0) = 0;
    error_covariance(1,1) = 1;

    tweak_gyro(); // 初回のジャイロオフセット補正
}

int Gyro::get_azimuth() {
    sensors_event_t event;
    bno.getEvent(&event);
    heading = (int)event.orientation.x + dir_offset;
    azimuth = heading + 180;
    if (azimuth > 360) {
        azimuth -= 360;
    } else if (azimuth < 0) {
        azimuth += 360;
    }
    return azimuth;
}

int Gyro::get_yaw() {
    yawcurrenttime = millis();
    yawdt = (yawcurrenttime - yawlastupdatetime) / 1000;
    yawlastupdatetime = yawcurrenttime;

    imu::Vector<3> gyro_data = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    float velocity_z = gyro_data.z() - gyro_offset;

    // **定期的にオフセット補正**
    if (millis() - last_gyro_offset_update > gyro_update_interval && abs(velocity_z) < 0.1f) {
        tweak_gyro();
        last_gyro_offset_update = millis(); // 更新タイミングを記録
    }

    // カルマンフィルタ予測ステップ
    state_vector = transition_matrix * state_vector;
    error_covariance = transition_matrix * error_covariance * transition_matrix.transpose() + process_noise;

    // 観測更新
    measurement(0) = gyro.get_yawfromquat(bno.getQuat());
    Eigen::MatrixXd kalman_gain = error_covariance * observation_matrix.transpose() * (observation_matrix * error_covariance * observation_matrix.transpose() + observation_noise).inverse();
    state_vector = state_vector + kalman_gain * (measurement - observation_matrix * state_vector);
    error_covariance = (Eigen::MatrixXd::Identity(2, 2) - kalman_gain * observation_matrix) * error_covariance;

    return (int)state_vector(0);
}

void Gyro::get_cord() {
    cordcurrenttime = millis();
    corddt = (cordcurrenttime - cordlastupdatetime) / 1000;
    cordlastupdatetime = cordcurrenttime;
    sensors_event_t accelEvent;
    bno.getEvent(&accelEvent, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    accel_x = float(accelEvent.acceleration.x);
    accel_y = float(accelEvent.acceleration.y);
    gyro_z = gyro.get_yaw();
    if (gyro_z < -180) {
        gyro_z += 360;
    } else if (gyro_z > 180) {
        gyro_z -= 360;
    }
    theta += gyro_z * corddt; //角度更新

    bool collision_stat = (abs(accel_x) > collision_border); //衝突検知

    if (!collision_stat) {
        //回転座標に変換してコート視点の座標に調整
        accel_x_rot = accel_x * cos(theta) - accel_y * sin(theta);
        accel_y_rot = accel_x * sin(theta) + accel_y * cos(theta);

        gyro.tweak_kalman(); //カルマンフィルタ調整

        //UKF予測
        vel_x += accel_x_rot * corddt + process_noise;
        vel_y += accel_y_rot * corddt + process_noise;
        pos_x += vel_x * corddt;
        pos_y += vel_y * corddt;

        //EKF校正
        pos_x = (int)(pos_x + measurement_noise) * postweak ;
        pos_y = (int)(pos_x + measurement_noise) * postweak ;
    }
}

int Gyro::get_yawfromquat(const imu::Quaternion& quat) {
    float sinyawcospitch = 2.0f * (quat.w() * quat.z() + quat.x() * quat.y());
    float cosyawcospitch = 1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z());
    float yawradians = atan2(sinyawcospitch, cosyawcospitch);

    float yawdegrees = degrees(yawradians);
    if (yawdegrees < 0) yawdegrees += 360;
    return (int)yawdegrees;
}

void Gyro::tweak_kalman() {
    accelmagnitude = sqrt(accel_x * accel_x + accel_y * accel_y);
    if (accelmagnitude > 2.0) {  
        process_noise = 0.05;
        measurement_noise = 0.2;
    } else {
        process_noise = 0.01;
        measurement_noise = 0.1;
    }
}

void Gyro::tweak_gyro() {
    float sum = 0;
    int samples = 50; // サンプル数を少なくして頻繁に実行可能に

    for (int i = 0; i < samples; i++) {
        imu::Vector<3> gyro_data = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        sum += gyro_data.z();
        delay(5);
    }

    gyro_offset = sum / samples; // 平均値をオフセットとして保存
}

void Gyro::dir_reset() { //方向キャリブレーション
    dir_offset = gyro.get_yaw();
}

void Gyro::cord_reset() { //座標リセット
    pos_x = 0;
    pos_y = 0; 
}

void Gyro::cord_custom(int x, int y) {
    pos_x = x;
    pos_y = y;
}

void Gyro::restart() { //瞬間的にモードを変えることで初期化
    bno.setMode(OPERATION_MODE_CONFIG);
    delay(25);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(25);
}

int Gyro::get_x() {
    return pos_x;
}

int Gyro::get_y() {
    return pos_y;
}
