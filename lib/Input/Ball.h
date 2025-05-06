#include <Arduino.h>
#include <API.h>

class BALL {
    public:
        void setup();
        void read();
        int get_distance(short BallNum);//ボールの距離を取得する関数
        int get_direction();//ボールの方向を取得する関数

        int Ball_Values[16];//ボールの値を格納する配列

    private:
        //調整用
        const int BallDistance_offset = 2500;
        
        int Total_X = 0;
        int Total_Y = 0;
        byte BallNumStart;
        byte Max_BallNum = 0;
        byte Max_BallValue = 0;
        int Ball_Distance = 0;
        const int NUMBalls = 16;
        const int Ball_PIN[16] = {31, 29, 27, 25, 23, 19, 17, 15, 32, 34, 36, 38, 40, 42, 44, 46};
        const float Ball_Directions[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5}; // Direction of the ball 
};