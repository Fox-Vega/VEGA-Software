#include <MyPIXEL.h>


void MyPIXEL::MyPIXEL_Setup() {
        pixels.begin();
        pixels.setBrightness(PIXEL_Brightness);
}

void MyPIXEL::MyPIXEL_Uni(int PIXELNum, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        pixels.setPixelColor(PIXELNum, pixels.Color(Red, Green, Blue));
        pixels.show();
    }
}

void MyPIXEL::MyPIXEL_Multi(int PIXELNumStart, int PIXELNumEnd, int Red, int Green, int Blue) {
    if (USEPIXELS == true) {
        for (int i = PIXELNumStart; i <= PIXELNumEnd; i++) {
            pixels.setPixelColor(i, pixels.Color(Red, Green, Blue));
        }
        pixels.show();
    }
}

void MyPIXEL::MyPIXEL_Clear() {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Set all pixels to off
    }
    pixels.show();
}