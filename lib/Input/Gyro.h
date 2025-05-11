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
        int get_yaw(); //方位角取得（ドリフト対策有）
        int get_yawfromquat(const imu::Quaternion& quat); //ヨー取得
        void tweak_kalman(); //カルマンフィルタ調整
        void dir_reset(); //方向初期化
        void cord_reset(); //位置情報初期化
        void cord_custom(int x, int y); //自由位置に座標を設定可能
        void restart(); //センサーを初期化
        int get_x(); //座標のxを取得
        int get_y(); //座標のyを取得

    private:
        //調整用
        const float postweak = 1;//自己位置推定の値調整
        const float collision_border = 15.0;
        
        int heading;
        int offset;
        int roll;
        int azimuth;
        float dir_offset;
        float accelcm_x;
        float accelcm_y;
        float pitch;
        Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

        //自己位置推定用
        int quatyaw;
        float yaw;
        bool collision_stat;
        float pos_x = 0.0, pos_y = 0.0;
        float vel_x = 0.0, vel_y = 0.0;
        float theta = 0.0;
        float accel_x = 0.0, accel_y = 0.0; 
        float gyro_z = 0.0;
        float process_noise = 0.01; 
        float measurement_noise = 0.1;
        float accel_x_rot, accel_y_rot;
        float accelmagnitude;
        unsigned long corddt; //時間間隔
        unsigned long yawdt;
        unsigned long cordlastupdatetime = 0;
        unsigned long yawlastupdatetime = 0;
        unsigned long cordcurrenttime;
        unsigned long yawcurrenttime;
        const float filterCoefficient = 0.98f; // 相補フィルタ係数（高いほどジャイロを優先）
};
