#include <MyPIXEL.h>

void MyPIXEL::MyPIXEL_Setup() {
        pixels.begin();
        pixels.setBrightness(PIXEL_Brightness);
}

void MyPIXEL::MyPIXEL_Start(int PIXELNum, int Color[3]) {
    if (USEPIXELS == true) {
        pixels.setPixelColor(PIXELNum, pixels.Color(Color[0], Color[1], Color[2]));
        pixels.show();
    }
}

void MyPIXEL::MyPIXEL_Clear() {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Set all pixels to off
    }
    pixels.show();
}