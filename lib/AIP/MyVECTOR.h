#pragma once

#include <Arduino.h>

class MyVECTOR {
    public:
        void get_cordinate(float Azimuth, float Magnitude);//座標を取得する関数
        int get_azimuth(float X, float Y);//方位角を取得する関数
        int get_magnitude(float X, float Y);//距離を取得する関数
        int get_x();//取得したX座標を返す関数
        int get_y();//取得したY座標を返す関数

    private:
        float x;
        float y;
        float Theta;
        float Azimuth;
        float Magnitude;
};