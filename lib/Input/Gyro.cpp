#include <Input.h>
#include <Gyro.h>
#include <Eigen/Dense>

Eigen::VectorXd state_vector(4); // 状態ベクトル (yaw角, 角速度, pos_x, pos_y)
Eigen::MatrixXd error_covariance(4, 4); // 誤差共分散行列
Eigen::MatrixXd transition_matrix(4, 4); // 状態遷移行列
Eigen::MatrixXd observation_matrix(2, 4); // 観測行列
Eigen::MatrixXd process_noise(4, 4); // プロセスノイズ
Eigen::MatrixXd observation_noise(2, 2); // 観測ノイズ
Eigen::VectorXd measurement(2); // 観測データ (Yaw角, 加速度)

void Gyro::setup() {
    if (!bno.begin()) {
        Serial.println("BNO055 not detected.");
        while (1);
    }
    bno.setExtCrystalUse(true);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(1000);

    // **行列初期化**
    transition_matrix.setIdentity();
    transition_matrix(0, 1) = 0.01; // 角速度の影響を加味
    transition_matrix(2, 3) = 0.01; // 速度による座標更新

    observation_matrix.setZero();
    observation_matrix(0, 0) = 1; // Yaw角観測
    observation_matrix(1, 2) = 1; // 加速度観測

    process_noise.setZero();
    process_noise(1, 1) = 0.0001; // 角速度ノイズ
    process_noise(3, 3) = 0.0001; // 座標ノイズ

    observation_noise.setIdentity();
    observation_noise(0, 0) = 0.01; // Yawの観測誤差
    observation_noise(1, 1) = 0.02; // 加速度の観測誤差

    state_vector.setZero(); // 初期状態
    error_covariance.setIdentity(); // 誤差共分散

    tweak_gyro(); // 初回のジャイロオフセット補正
}

int Gyro::get_yaw() {
    yawcurrenttime = millis();
    yawdt = (yawcurrenttime - yawlastupdatetime) / 1000;
    yawlastupdatetime = yawcurrenttime;

    imu::Vector<3> gyro_data = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
    float velocity_z = gyro_data.z() - gyro_offset;

    // **定期的にオフセット補正**
    if (millis() - last_gyro_offset_update > 5000 && abs(velocity_z) < 0.1f) {
        tweak_gyro();
        last_gyro_offset_update = millis(); 
    }

    // **カルマンフィルタ予測ステップ**
    state_vector = transition_matrix * state_vector;
    error_covariance = transition_matrix * error_covariance * transition_matrix.transpose() + process_noise;

    // **観測更新**
    measurement(0) = gyro.get_yawfromquat(bno.getQuat());
    Eigen::MatrixXd kalman_gain = error_covariance * observation_matrix.transpose() * 
                                  (observation_matrix * error_covariance * observation_matrix.transpose() + observation_noise).inverse();
    state_vector += kalman_gain * (measurement - observation_matrix * state_vector);
    error_covariance = (Eigen::MatrixXd::Identity(4, 4) - kalman_gain * observation_matrix) * error_covariance;

    return (int)state_vector(0);
}

void Gyro::get_cord() {
    cordcurrenttime = millis();
    corddt = (cordcurrenttime - cordlastupdatetime) / 1000;
    cordlastupdatetime = cordcurrenttime;

    sensors_event_t accel_event;
    bno.getEvent(&accel_event, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    
    measurement(1) = accel_event.acceleration.x; // 加速度データ

    // **カルマンフィルタ座標更新**
    Eigen::MatrixXd kalman_gain = error_covariance.block<2,2>(2,2) * 
                                  (error_covariance.block<2,2>(2,2) + process_noise.block<2,2>(2,2)).inverse();
    state_vector.segment<2>(2) += kalman_gain * (measurement.segment<1>(1) - state_vector.segment<2>(2));

    pos_x = state_vector(2);
    pos_y = state_vector(3);
}

void Gyro::tweak_gyro() {
    float sum = 0;
    int samples = 50;

    for (int i = 0; i < samples; i++) {
        imu::Vector<3> gyro_data = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
        sum += gyro_data.z();
        delay(5);
    }

    gyro_offset = sum / samples;
}

void Gyro::dir_reset() {
    dir_offset = gyro.get_yaw();
}

void Gyro::cord_reset() {
    pos_x = 0;
    pos_y = 0; 
}

void Gyro::cord_custom(int x, int y) {
    pos_x = x;
    pos_y = y;
}

void Gyro::restart() {
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
