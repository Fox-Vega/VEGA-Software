#pragma once

#include <Arduino.h>


class General {
    public:
        void setup(); //初期設定
        int startup(); //設定
        int check_run(); //タクトスイッチを確認し、実行していいかを確認
        int check_mode(); //モードを確認
        void update(); //値を更新

    private:
        short mode = 0; //機体モード
        short phase = 0; //設定フェーズ
        short switch_pressed; //押されたスイッチ
        bool toggle_stat; //トグルスイッチの状態
        bool Run = false; //実行するかどうか
};