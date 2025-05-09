#pragma once

#include <Arduino.h>

class MyVECTOR {
    public:
        void get_cord(float Azimuth, float Magnitude);//座標を取得する関数
        void get_ppcord(float Pl_x, float Pl_y, float Po_x, float Po_y);//player to positionの座標
        int get_azimuth(float X, float Y);//方位角を取得する関数
        int get_magnitude(float X, float Y);//距離を取得する関数
        int get_x();//取得したX座標を返す関数
        int get_y();//取得したY座標を返す関数
        int get_psx();//plから見たpoの座標を返す関数
        int get_psy();//plから見たpoの座標を返す関数

    private:
        float x;
        float y;
        float Ps_x;
        float Ps_y;
        float Theta;
        float Azimuth;
        float Magnitude;
};
