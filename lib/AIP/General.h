#pragma once

#include <Arduino.h>

class General {
    public:
        void setup();
        int startup();
        int check_run();
        short mode = 0;

    private:
        bool Run_p = false;//実行するかどうか
        short phase = 0;
        short switch_pressed;
        bool toggle_stat;
};