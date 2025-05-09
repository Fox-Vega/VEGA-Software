#pragma once

#include <Arduino.h>

class MyVECTOR {
    public:
        void get_cord(float azimuth, float magnitude);//座標を取得する関数
        void get_ppcord(float pl_x, float pl_y, float po_x, float po_y);//player to positionの座標
        int get_azimuth(float x, float y);//方位角を取得する関数
        int get_magnitude(float x, float y);//距離を取得する関数
        int get_x();//取得したX座標を返す関数
        int get_y();//取得したY座標を返す関数
        int get_psx();//plから見たpoの座標を返す関数
        int get_psy();//plから見たpoの座標を返す関数

    private:
        float x;
        float y;
        float ps_x;
        float ps_y;
        float theta;
        float azimuth;
        float magnitude;
};
