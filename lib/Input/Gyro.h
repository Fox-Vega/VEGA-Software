#include <Arduino.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Gyro {
    public:
        void GyroSetup();
        void GyroRead();
        int GetAzimuth();
        void GetPosition();
        void TweakKalman();
        void GyroReset();

        float Accelcm_X;
        float Accelcm_Y;
        float heading;
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