#pragma once

#include <Arduino.h>


class General {
    public:
        void setup(); //初期設定
        int startup(); //設定
        int check_run(); //タクトスイッチを確認し、実行していいかを確認
        int check_mode(); //モードを確認
        void update(); //値を更新
        int calculate_deg(char mode, int num1, int num2);//角度計算
        /*
        A:加算（slow）
        a:加算（fast）
        S:減算（slow）
        s:減算（fast）＜＜＜むずい、先に乗算やって後で頑張る！
        */
        int cal_d(char mode, int num1, int num2);//上の略
        /*
        関数の中で関数呼び出してるから速度が必要なときにはわざわざ上を入力した方が良いかも
        */
    private:
        byte startcord = 0;
        bool toggle_stat; //トグルスイッチの状態
        bool Run = false; //実行するかどうか
        short mode = 0; //機体モード
        short phase = 0; //設定フェーズ
        //スタート座標　通常　右奥　左奥　右前　左前　
        short startcords_x[5] = {0, 0, 0, 0, 0}; //スタート位置のx座標
        short startcords_y[5] = {0, 0, 0, 0, 0}; //スタート位置のy座標
        short startPIXELs[5] = {1, 3, 15, 7, 11};
        short switch_pressed; //押されたスイッチ
};