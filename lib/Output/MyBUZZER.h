#pragma once


#include <Arduino.h>


class MyBUZZER {
    public:
        void MyBUZZER_Start(int BUZZERNote, int BUZZERDuration);
        void MyBUZZER_Preset(int BUZZERPresetNum);

    private:
        const int BUZZER_PIN = 47; // Pin where the Buzzer is connected
};