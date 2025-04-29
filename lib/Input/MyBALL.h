#include <Arduino.h>

class MyBALL {
    public:
        void MyBALL_Setup();
        int MyBALL_Check();
        int Detected_BALL[16]; // Variable to store the detected ball number

    private:
        const int NUMBALLS = sizeof(BALL_PIN[0]) / sizeof(BALL_PIN[16]); // Number of lines in the sensor array
        const int BALL_PIN[16] = {
            31, 29, 27, 25, 23, 19, 17, 15, 32, 34, 36, 38, 40, 42, 44, 46
        }; // Pin where the line sensor is connected
};