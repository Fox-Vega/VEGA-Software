#include <Arduino.h>

class MOTOR {
    public:
        void move(int Azimuth, int Power_);
        void turn(int Power_);//マイナスの値を入れても大丈夫
        void brake();

    private:
        //調整用
        short speed = 100;

        int Power;//モーター用出力
        bool PoMi;//positiveはtrue、minusはfalse
        short motor_PIN1[4] = {8, 7, 5, 3};
        short motor_PIN2[4] = {9, 6, 4, 2};
        int motor_x[4];
        int motor_y[4];
        short AzimuthM;//モーターから見た方位角（一時保存用）
        short motor_degrees[4] = {45, 135, 225, 315};
};