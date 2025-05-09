#pragma once

#include <Arduino.h>


class General {
    public:
        void setup();
        int startup();
        int check_run();
        int check_mode();
        void update();

    private:
        short mode = 0;
        short phase = 0;
        short switch_pressed;
        bool toggle_stat;
        bool Run = false;//実行するかどうか
};