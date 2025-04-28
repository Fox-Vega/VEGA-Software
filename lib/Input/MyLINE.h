#include <Arduino.h>

class MyLINE {
    public:
        void MyLINE_Setup();
        void MyLINE_End();

    private:
        const int NUMLINES = sizeof LINE_PIN[0] / LINE_PIN[24]; // Number of lines in the sensor array
        const int LINE_PIN[24] = {}; // Pin where the line sensor is connected
};