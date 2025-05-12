#pragma once

#include <Arduino.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Gyro {
    public:
        void setup(); //初期設定
        int get_azimuth(); //方位角取得（ドリフト対策無）
        void get_cord(); //自己位置取得
        void dir_reset(); //方向初期化
        void cord_reset(); //位置情報初期化
        void cord_custom(int x, int y); //自由位置に座標を設定可能
        void restart(); //センサーを初期化
        int get_x(); //座標のxを取得
        int get_y(); //座標のyを取得
        float vector_norm(const float v[3]) {
            return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
        }

    private:
        //調整用
        const float shock_threshold = 15.0; //衝撃判定
        const float dt = 0.1;
        
        int azimuth;
        float accel_bias[3] = {0.0, 0.0, 0.0};
        unsigned long lastupdate;
        Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

        //自己位置推定用
        float states[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; 
        int pos[3];
};
