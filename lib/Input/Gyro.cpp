#include <Gyro.h>
#include <Input.h>

void Gyro::GyroSetup() {
    Serial.begin(9600);
    bno.setExtCrystalUse(true);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(25);
    lastUpdateTime = millis();
}

void Gyro::GyroRead() {
    sensors_event_t event;
    bno.getEvent(&event);
    heading = event.orientation.x;
    roll = event.orientation.y;
    pitch = event.orientation.z;
}

int Gyro::GetAzimuth() {
    gyro.GyroRead();
    int int_heading = (int)heading;
    return int_heading;
}

void Gyro::GetPosition() {
    currentTime = millis();
    dt = (currentTime - lastUpdateTime) / 1000.0;
    lastUpdateTime = currentTime;
    sensors_event_t accelEvent, gyroEvent;
    bno.getEvent(&accelEvent, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    bno.getEvent(&gyroEvent, Adafruit_BNO055::VECTOR_GYROSCOPE);
    accelX = accelEvent.acceleration.x;
    accelY = accelEvent.acceleration.y;
    gyroZ = gyroEvent.gyro.z;
    theta += gyroZ * dt; //角度更新

    //回転座標に変換してコート視点の座標に調整
    accelX_rot = accelX * cos(theta) - accelY * sin(theta);
    accelY_rot = accelX * sin(theta) + accelY * cos(theta);

    TweakKalman(); // カルマンフィルタを調整

    //UKF予測
    velX += accelX_rot * dt + processNoise;
    velY += accelY_rot * dt + processNoise;
    posX += velX * dt;
    posY += velY * dt;

    //EKF校正
    posX += measurementNoise;
    posY += measurementNoise;
}

void Gyro::TweakKalman() {
    accelMagnitude = sqrt(accelX * accelX + accelY * accelY);
    if (accelMagnitude > 2.0) {  
        processNoise = 0.05;
        measurementNoise = 0.2;
    } else {
        processNoise = 0.01;
        measurementNoise = 0.1;
    }
}

void Gyro::GyroReset() {
    bno.setMode(OPERATION_MODE_CONFIG);
    delay(25);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(25);
}

