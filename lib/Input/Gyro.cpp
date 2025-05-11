#include <Input.h>
#include <Gyro.h>

void Gyro::setup() {
    if (!bno.begin()) {
        Serial.println("BNO055 not detected.");
        while (1);  // センサー未検出時は停止
    }
    bno.setExtCrystalUse(true);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(1000);
    quatyaw = gyro.get_yawfromquat(bno.getQuat());
    cordlastupdatetime = millis();
    yawlastupdatetime = millis();
}

void Gyro::read() {
    sensors_event_t event;
    bno.getEvent(&event);
    heading = (int)event.orientation.x + dir_offset;
}

int Gyro::get_azimuth() {
    gyro.read();
    azimuth = (int)heading + 180;
    if (azimuth > 360) {
        azimuth -= 360;
    } else if (azimuth < 0) {
        azimuth += 360;
    }
    return azimuth;
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

int Gyro::get_yaw() {
    yawcurrenttime = millis();
    yawdt = (yawcurrenttime - yawlastupdatetime) / 1000.0;
    yawlastupdatetime = yawcurrenttime;

    // ジャイロZ軸の角速度を取得（rad/s）
    imu::Vector<3> gyrodata = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    float angularvelocity_z = gyrodata.z();

    // 積分して現在のYawを更新（加算）
    yaw += angularvelocity_z * yawdt;

    // センサー内部の方向推定（クォータニオン）から得られるYawを参照値として取得
    float referenceYaw = gyro.get_yawfromquat(bno.getQuat());

    // Yawの誤差を -180〜180 度に補正（360度ラップを回避）
    float yawerorr = referenceYaw - yaw;
    if (yawerorr > 180) yawerorr -= 360;
    if (yawerorr < -180) yawerorr += 360;
    
    // 相補フィルタを用いてYawを補正（地磁気参照の揺れを滑らかに）
    yaw += (1.0f - filterCoefficient) * yawerorr;
    
    if (yaw < 0) yaw += 360;
    if (yaw >= 360) yaw -= 360;
    return (int)yaw;
}

int Gyro::get_yawfromquat(const imu::Quaternion& quat) {
    float sinyawcospitch = 2.0f * (quat.w() * quat.z() + quat.x() * quat.y());
    float cosyawcospitch = 1.0f - 2.0f * (quat.y() * quat.y() + quat.z() * quat.z());

    // ラジアン角を取得
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

void Gyro::dir_reset() { //方向キャリブレーション
    gyro.read();
    dir_offset = float(gyro.get_azimuth());
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