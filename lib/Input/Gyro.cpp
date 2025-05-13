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
    
}

void Gyro::get_cord() {
    //BNO055から加速度データを取得（単位：m/s^2）
    for (i = 0; i < 2; i++) {
        float dt = millis() - old_cordtime;
        dt2 += dt;
        sensors_event_t acccel_event;
        bno.getEvent(&accel_event, Adafruit_BNO055::VECTOR_LINEARACCELEROMETER);
        float a[3] = {accel_event.acceleration.x, accel_event.acceleration.y, accel_event.acceleration.z };
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
    return states[0];
}

int Gyro::get_y() {
    return states[1];
}
