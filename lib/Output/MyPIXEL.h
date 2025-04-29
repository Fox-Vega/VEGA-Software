#pragma once


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class MyPIXEL {
    public:
        void MyPIXEL_Setup();
        void MyPIXEL_Uni(int PIXELNum, int Red, int Green, int Blue);
        void MyPIXEL_Multi(int PIXELNumStart, int PIXELNumEnd, int Red, int Green, int Blue);
        void MyPIXEL_Clear();
    private:
        //ajustments
        const bool USEPIXELS = true; // Set to true to use NeoPixels, false to disable
        const int PIXEL_Brightness = 255; // Set to 0 for darkest and 255 for brightest
        // NeoPixel setup
        const int PIXEL_PIN = 45; // Pin where the NeoPixel ring is connected
        const int NUMPIXELS = 16; // Number of pixels in the strip
        Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
};

// Color presets
// int Red[3] = {255, 0, 0};
// int Yellow[3] = {255, 255, 0};
// int Green[3] = {0, 255, 0};
// int Blue[3] = {0, 0, 255};
// int Purple[3] = {255, 0, 255};
// int White[3] = {255, 255, 255};