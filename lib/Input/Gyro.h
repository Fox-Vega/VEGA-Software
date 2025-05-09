#pragma once

#include <Arduino.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Gyro {
    public:
        void setup();//初期設定
        void read();//センサーデータ取得
        int get_azimuth();//方位角取得
        void get_cord();//自己位置取得
        void tweak_kalman();//カルマンフィルタ調整
        void dir_reset();//方向を初期化
        void cord_reset();//位置情報を初期化
        void restart();//BNO055自体を初期化

        float accelcm_x;
        float accelcm_y;
        int heading;
        int offset;
        int roll;
        float pitch;

        //自己位置推定用
        float pos_x = 0.0, pos_y = 0.0;
        float vel_x = 0.0, vel_y = 0.0;
        float theta = 0.0;
        float accel_x = 0.0, accel_y = 0.0; 
        float gyro_z = 0.0;
        float process_noise = 0.01; 
        float measurement_noise = 0.1;
        unsigned long lastupdatetime = 0;
        unsigned long current_time;
        unsigned long dt; //時間間隔
        float accel_x_rot;
        float accel_y_rot;
        float accelmagnitude;
        
    private:
        //調整用
        const float postweak = 1;//自己位置推定の値調整
        
        Adafruit_BNO055 bno = Adafruit_BNO055(55);
        float dir_offset;
};
