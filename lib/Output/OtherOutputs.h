#pragma once


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


// 色の参考
// int red[3] = {255, 0, 0};
// int Yellow[3] = {255, 255, 0};
// int green[3] = {0, 255, 0};
// int blue[3] = {0, 0, 255};
// int Purple[3] = {255, 0, 255};
// int White[3] = {255, 255, 255};


class MyPIXEL {
    public:
        void setup(); //初期設定
        void brightness(int brightness); //ネオピクの明るさ調整　999にすると既定値になる
        void uni(int PIXELNUM, int red, int green, int blue); //単ピクセル点灯
        void multi(int PIXELNUMstart, int PIXELNUMend, int red, int green, int blue); //連続ピクセル点灯
        void unis(int PIXELNUM, int red, int green, int blue); //試合前用単ピクセル点灯
        void multis(int PIXELNUMstart, int PIXELNUMend, int red, int green, int blue); //試合前用連続ピクセル点灯
        void closest(int azimuth, int red, int green, int blue); //入力角度に最も近いピクセル点灯
        void clear(); //全消灯
        
    private:
        //調整用
        const bool usePIXEL = true; //ネオピクセルの使用有無
        const int PIXELbrightness = 255; //最大で255
        
        const byte PIXELPIN = 45; // Pin where the NeoPixel ring is connected
        const byte NUMPIXEL = 16; // NUMber of pixels in the strip
        Adafruit_NeoPixel PIXEL = Adafruit_NeoPixel(NUMPIXEL, PIXELPIN, NEO_GRB + NEO_KHZ800);
};


class MyBUZZER {
    public:
        void setup();
        void start(int BUZZERnote, int BUZZERduration); //音程、音長さを指定して音を鳴らす
        void preset(int BUZZERpresetNUM); //既定の音を鳴らす

    private:
        const byte BUZZER_PIN = 47;
};