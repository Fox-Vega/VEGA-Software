#pragma once

#include <Arduino.h>
#include <API.h>

class BALL {
    public:
        void setup();
        void read();
        int get_value(short BallNum);//ボールの値を取得する関
        int get_magnitude();//ボールの距離を計算する関数
        int get_azimuth();//ボールの方向を取得する関数

        int ballvalues[16];//ボールの値を格納する配列

    private:
        //調整用
        const int ballvalue_offset = 2500;
        
        float ballvalue;
        int total_x = 0;
        int total_y = 0;
        byte ballNUMstart;
        byte max_ballNUM = 0;
        byte max_ballvalue = 0;
        const int NUMball = 16;
        const int ballPINs[16] = {31, 29, 27, 25, 23, 19, 17, 15, 32, 34, 36, 38, 40, 42, 44, 46};
        const float balldirs[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5}; // Direction of the ball 
};
