#include <Arduino.h>

class MyBALL {
    public:
        int MyBALL_GetAngle();
        int MyBALL_GetDistance();
        int MyBALL_GetSpeed();

    private:
        const int NUMBALLS = sizeof BALL_PIN[0] / BALL_PIN[16]; // Number of lines in the sensor array
        const int BALL_PIN[16] = {}; // Pin where the line sensor is connected
};