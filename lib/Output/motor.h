#pragma once

#include <Arduino.h>

class MyMOTOR {
    public:
        void setup();
        void run(float movement_azimuth, int power_, int dir_azimuth);//進む方向、力（最大Powerは255）、向く方向（姿勢制御用）を引数にいれる
        int difix(int setpoint);//PID姿勢制御用
        void free();//自由回転
        void brake();//ブレーキ

    private:
        //調整用
        double kp = 2.0;//比例 を大きくすると応答が速くなるが、振動しやすくなる
        double ki = 0.5;//積分 を大きくすると誤差が蓄積されにくくなるが、過剰補正のリスク
        double kd = 1.0;//微分 を大きくすると急激な変化を抑えられるが、ノイズの影響を受けやすい
        int pwmscale = 0.71;//補正速度

        int difix_PWM;
        int motorPWM;
        int Power;//進行方向参考した場合のモーター出力
        bool PoMi;//正・負を判断するため
        bool difix_PoMi;
        const short motor_PIN1[4] = {8, 7, 5, 3};
        const short motor_PIN2[4] = {9, 6, 4, 2};
        short motor_PWM1[4];
        short motor_PWM2[4];
        int motor_x[4];
        int motor_y[4];
        short azimuth_motor;//モーターから見た進行方向の方位角（一時保存用）
        short motor_degrees[4] = {45, 135, 225, 315};
        double integral;
        double prev_error;
        double derivative;
};