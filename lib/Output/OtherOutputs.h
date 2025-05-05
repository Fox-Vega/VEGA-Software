#pragma once


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


// 色の参考
// int Red[3] = {255, 0, 0};
// int Yellow[3] = {255, 255, 0};
// int Green[3] = {0, 255, 0};
// int Blue[3] = {0, 0, 255};
// int Purple[3] = {255, 0, 255};
// int White[3] = {255, 255, 255};


class MyPIXEL {
    public:
        void MyPIXEL_Setup();
        void MyPIXEL_Uni(int PIXELNum, int Red, int Green, int Blue);
        void MyPIXEL_Multi(int PIXELNumStart, int PIXELNumEnd, int Red, int Green, int Blue);
        void MyPIXEL_Closest(int Azimuth, int Red, int Green, int Blue);
        void MyPIXEL_Clear();
        
    private:
        //調整用
        const bool USEPIXELS = true; //ネオピクセルの使用有無
        const int PIXEL_Brightness = 255; //最大で255
        
        const int PIXEL_PIN = 45; // Pin where the NeoPixel ring is connected
        const int NUMPIXELS = 16; // Number of pixels in the strip
        Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
};


class MyBUZZER {
    public:
        void MyBUZZER_Start(int BUZZERNote, int BUZZERDuration);
        void MyBUZZER_Preset(int BUZZERPresetNum);

    private:
        const int BUZZER_PIN = 47;
};