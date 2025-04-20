#include <MyPIXEL.h>

void MyPIXEL::MyPIXEL_Start(int NumPIXEL, int Color[3]) {
    pixels.begin();
    pixels.setBrightness(PIXEL_Brightness);
    pixels.setPixelColor(NumPIXEL, pixels.Color(Color[0], Color[1], Color[2]));
    pixels.show();
}

void MyPIXEL::MyPIXEL_Clear() {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Set all pixels to off
    }
    pixels.show();
}