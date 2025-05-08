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
        void get_position();//自己位置取得
        void tweak_kalman();//カルマンフィルタ調整
        void dir_reset();//方向を初期化
        void pos_reset();//位置情報を初期化
        void restart();//BNO055自体を初期化

        float Accelcm_X;
        float Accelcm_Y;
        float heading;
        float offset;
        float roll;
        float pitch;
        //自己位置推定用
        float posX = 0.0, posY = 0.0;
        float velX = 0.0, velY = 0.0;
        float theta = 0.0;
        float accelX = 0.0, accelY = 0.0; 
        float gyroZ = 0.0;
        float processNoise = 0.01; 
        float measurementNoise = 0.1;
        unsigned long lastUpdateTime = 0;
        unsigned long currentTime;
        float dt; //時間間隔
        float accelX_rot;
        float accelY_rot;
        float accelMagnitude;
        
    private:
        Adafruit_BNO055 bno = Adafruit_BNO055(55);
};
