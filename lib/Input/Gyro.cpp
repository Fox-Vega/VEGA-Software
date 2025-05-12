#include <Input.h>
#include <AIP.h>
#include <Gyro.h>
#include <math.h>

void Gyro::setup() {
    if (!bno.begin()) {
        Serial.println("BNO055 not detected.");
        while (1);  //センサー未検出時は停止
    }
    bno.setExtCrystalUse(true);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(1000);
    azimuth = 0;
    sensors_event_t event;
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    float a[3] = { event.acceleration.x, event.acceleration.y, event.acceleration.z };
    while (millis() < 5000) {
        for (int i = 0; i < 3; i++) {
            accel_bias[i] = (accel_bias[i] + a[i]) * 0.5; //平均値を計算
        }
    }
}

void Gyro::get_cord() {
    //BNO055から加速度データを取得（単位：m/s^2）
    unsigned long delaytime = millis() - lastupdate;
    if (delaytime> (dt * 1000)) {
        sensors_event_t event;
        bno.getEvent(&event, Adafruit_BNO055::VECTOR_ACCELEROMETER);
        float a[3] = { event.acceleration.x, event.acceleration.y, event.acceleration.z };
        for (int i = 0; i < 3; i++) {
            a[i] -= accel_bias[i]; //バイアスを補正
        } 
        for (int i = 0; i < 3; i++) {
            if (a[i] < 0.1) {
                a[i] = 0;
            }
        } 

        const float shock_threshold = 15.0;
        if (vector_norm(a) > shock_threshold) {
            a[0] = a[1] = a[2] = 0.0;
        }

        for (int i = 3; i < 6; i++) {
            if (states[i] < 0.2) {
                states[i] = 0;
            }
        }
        //状態予測：位置と速度を積分
        for (int i = 0; i < 3; i++) {
            states[i] += states[i + 3] * dt;  //位置更新
            states[i + 3] += a[i] * dt;      //速度更新
        }

        //簡易補正（定数ゲイン補正）
        const float gain = 0.0909;
        for (int i = 0; i < 3; i++) {
            states[i] += gain * (a[i] * dt);  //位置補正
            states[i + 3] += gain * (a[i] * dt);  //速度補正
        }

        //出力の単位変換（m → cm）
        for (int i = 0; i < 3; i++) {
            pos[i] = (int)(states[i] * 100.0);
        }
    }
    Serial.print(">PosX:");
    Serial.println(states[0]);
    Serial.print(">PosY:");
    Serial.println(states[1]);
}

void Gyro::restart() { //瞬間的にモードを変えることで初期化
    bno.setMode(OPERATION_MODE_CONFIG);
    delay(25);
    bno.setMode(OPERATION_MODE_IMUPLUS);
    delay(25);
}

int Gyro::get_x() {
    return states[0];
}

int Gyro::get_y() {
    return states[1];
}
