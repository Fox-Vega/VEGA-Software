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
        void setup();//初期設定
        void uni(int PIXELNum, int Red, int Green, int Blue);//単ピクセル点灯
        void multi(int PIXELNumStart, int PIXELNumEnd, int Red, int Green, int Blue);//連続ピクセル点灯
        void closest(int Azimuth, int Red, int Green, int Blue);//入力角度に最も近いピクセル点灯
        void clear();//全消灯
        
    private:
        //調整用
        const bool usePIXEL = true; //ネオピクセルの使用有無
        const int PIXEL_Brightness = 255; //最大で255
        
        const int PIXELPIN = 45; // Pin where the NeoPixel ring is connected
        const int NUMPIXEL = 16; // Number of pixels in the strip
        Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXEL, PIXELPIN, NEO_GRB + NEO_KHZ800);
};


class MyBUZZER {
    public:
        void setup();
        void start(int BUZZERnote, int BUZZERduration);//トーン、音の長さを指定して音を鳴らす
        void preset(int BUZZERpresetNUM);//あらかじめ設定された音を鳴らす

    private:
        const int BUZZER_PIN = 47;
};