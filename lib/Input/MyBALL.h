#include <Arduino.h>

class MyBALL {
    public:
        void MyBALL_Setup();
        int MyBALL_Read();
        int Get_BALLDistance();
        int BALL_Values_[16];
        int BALL_Values[16]; //Final ball values

    private:
        // Adjustments
        const int BALLDistance_offset = 2500;
        int Max_BALLValue = 0; // Maximum value for the ball sensor
        int Max_BALLNum = 0; // Maximum ball sensor pin number
        int BALL_Distance = 0; // Distance of the ball from the sensor
        const int NUMBALLS = sizeof(BALL_PIN[0]) / sizeof(BALL_PIN[16]); // Number of lines in the sensor array
        const int BALL_PIN[16] = {
            31, 29, 27, 25, 23, 19, 17, 15, 32, 34, 36, 38, 40, 42, 44, 46
        }; 
};