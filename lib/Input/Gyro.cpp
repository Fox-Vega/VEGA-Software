#include <Input.h>
#include <AIP.h>
#include <Gyro.h>
#include <math.h>

void Gyro::setup() {
    Wire.begin();
    if (!bno.begin()) {
        Serial.println("BNO055 not detected.");
        while (1);  //センサー未検出時は停止
    }
    bno.setExtCrystalUse(true);
    bno.setMode(OPERATION_MODE_AMG);
    delay(1000);
    azimuth = 0;
    while (millis() < 5000) {
        sensors_event_t event;
        bno.getEvent(&event, Adafruit_BNO055::VECTOR_LINEARACCELEROMETER);  
        float a[3] = { event.acceleration.x, event.acceleration.y, event.acceleration.z };
        for (int i = 0; i < 3; i++) {
            accel_bias[i] = (accel_bias[i] + a[i]) * 0.5; //平均値を計算
        }
    }
}

int Gyro::get_azimuth() {
    sensors_event_t gyro_event, mag_event;
    bno.getEvent(&gyro_event, Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno.getEvent(&mag_event, Adafruit_BNO055::VECTOR_MAGNETOMETER);

    float dt = (float)(millis()- old_azimuthtime);
    old_azimuthtime = millis();

    // **ジャイロデータから角度を積分**
    float gyroYawRate = gyro_event.gyro.z; // 角速度 [°/s]
    float gyroAzimuth = azimuth + gyroYawRate * dt; // 積分で推定

    // **磁気センサーから絶対方位を取得**
    float magAzimuth = degrees(atan2(mag_event.magnetic.y, mag_event.magnetic.x));
    if (magAzimuth < 0) magAzimuth += 360; // 0~360°に調整

    // **相補フィルタを適用**
    azimuth = alpha * gyroAzimuth + (1 - alpha) * magAzimuth;

    return azimuth;
}

void Gyro::get_cord() {
    //BNO055から加速度データを取得（単位：m/s^2）
    for (i = 0; i < 2; i++) {
        float dt = (float)(millis() - old_cordtime);
        dt2 += dt;
        sensors_event_t acccel_event;
        sensors_event_t euler_event;
        bno.getEvent(&accel_event, Adafruit_BNO055::VECTOR_LINEARACCELEROMETER);
        float a[3] = {accel_event.acceleration.x, accel_event.acceleration.y, accel_event.acceleration.z };
        
        bno.getEvent(&euler_event, Adafruit_BNO055::VECTOR_EULER);
        float yaw_rad = radians(euler_event.orientation.x + yawtweak); // Yawをラジアンに変換
        
        for (int i = 0; i < 3; i++) {
            a[i] -= accel_bias[i]; //バイアスを補正
        } 
        for (int i = 0; i < 3; i++) {
            if (a[i] < accel_noise) {
                a[i] = 0;
            }
        } 

        if (a[0] > collision_border || a[1] > collision_border) {
            a[0] = a[1] = a[2] = 0.0;
        }
        lowpassvalue_x = lowpassvalue_x * filterCoefficient + a[0] * (1 - filterCoefficient);
        lowpassvalue_y = lowpassvalue_y * filterCoefficient + a[1] * (1 - filterCoefficient);
        highpassvalue_x = a[0] - lowpassvalue_x;
        highpassvalue_y = a[1] - lowpassvalue_y;
        
        speed_x += ((highpassvalue_x + old_accel_x) * dt) / 2 + speed_x;
        speed_y += ((highpassvalue_y + old_accel_y) * dt) / 2 + speed_y;
        old_accel_x = highpassvalue_x;
        old_accel_y = highpassvalue_y;
        old_speed_x = speed_x;
        old_speed_y = speed_y;
        old_cordtime = millis()
    }
    states[0] += speed_x / 2 * dt2;
    states[1] += speed_y / 2 * dt2;
    float world_x = states[0] * cos(-yaw_rad) - states[1] * sin(-yaw_rad);
    float world_y = states[0] * sin(-yaw_rad) - states[1] * cos(-yaw_rad);

    speed_x = 0;
    speed_y = 0;
        
    Serial.print(">PosX:");
    Serial.println(states[0]);
    Serial.print(">PosY:");
    Serial.println(states[1]);
}

void Gyro::restart() { //瞬間的にモードを変えることで初期化
    bno.setMode(OPERATION_MODE_CONFIG);
    delay(25);
    bno.setMode(OPERATION_MODE_AMG);
    delay(1000);
    while (millis() < 5000) {
        sensors_event_t event;
        bno.getEvent(&event, Adafruit_BNO055::VECTOR_LINEARACCELEROMETER);  
        float a[3] = { event.acceleration.x, event.acceleration.y, event.acceleration.z };
        for (int i = 0; i < 3; i++) {
            accel_bias[i] = (accel_bias[i] + a[i]) * 0.5; //平均値を計算
        }
    }
}

int Gyro::get_x() {
    return world_x;
}

int Gyro::get_y() {
    return world_y;
}
