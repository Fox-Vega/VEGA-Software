#include <Input.h>

void Gyro::setup() {
    bno.setExtCrystalUse(true);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(25);
    lastupdatetime = millis();
}

void Gyro::read() {
    sensors_event_t event;
    bno.getEvent(&event);
    heading = int(event.orientation.x + dir_offset);
    //roll = int(event.orientation.y);
    //pitch = int(event.orientation.z);
}

int Gyro::get_azimuth() {
    gyro.read();
    azimuth = heading + 180;
    if (azimuth > 360) {
        azimuth -= 360;
    } else if (azimuth < 0) {
        azimuth += 360;
    }
    return azimuth;
}

void Gyro::get_cord() {
    current_time = millis();
    dt = (current_time - lastupdatetime) / 1000;
    lastupdatetime = current_time;
    sensors_event_t accelEvent, gyroEvent;
    bno.getEvent(&accelEvent, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    bno.getEvent(&gyroEvent, Adafruit_BNO055::VECTOR_GYROSCOPE);
    accel_x = float(accelEvent.acceleration.x);
    accel_y = float(accelEvent.acceleration.y);
    gyro_z = gyroEvent.gyro.z + dir_offset;
    if (gyro_z < -180) {
        gyro_z += 360;
    } else if (gyro_z > 180) {
        gyro_z -= 360;
    }
    theta += gyro_z * dt; //角度更新

    bool collision_stat = (abs(accel_x) > collision_border); //衝突検知

    if (!collision_stat) {
        //回転座標に変換してコート視点の座標に調整
        accel_x_rot = accel_x * cos(theta) - accel_y * sin(theta);
        accel_y_rot = accel_x * sin(theta) + accel_y * cos(theta);

        tweak_kalman(); //カルマンフィルタを調整

        //UKF予測
        vel_x += accel_x_rot * dt + process_noise;
        vel_y += accel_y_rot * dt + process_noise;
        pos_x += vel_x * dt;
        pos_y += vel_y * dt;

        //EKF校正
        pos_x = (pos_x + measurement_noise) * postweak ;
        pos_y = (pos_x + measurement_noise) * postweak ;
    }
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
