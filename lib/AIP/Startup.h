#pragma once

#include <Arduino.h>

class Startup {
    public:
        void setup();
        void startup();
    private:
        bool Run = false;
        short mode = 0;
        short phase = 0;
        short switch_pressed;
        bool toggle_stat;
};
