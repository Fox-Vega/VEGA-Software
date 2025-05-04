#include <Arduino.h>
#include <API.h>

class MyBALL {
    public:
        void MyBALL_Setup();
        int MyBALL_Read();
        int Get_BALLDistance();
        int Get_BALLDirection();
        int BALL_Values[16]; //Final ball values

    private:
        // Adjustments
        const int BALLDistance_offset = 2500;

        int Total_X = 0;
        int Total_Y = 0;
        byte BALLNumStart;
        byte Max_BALLNum = 0; // Maximum ball sensor pin number
        byte Max_BALLValue = 0; // Maximum value for the ball sensor
        int BALL_Distance = 0; // Distance of the ball from the sensor
        const int NUMBALLS = sizeof(BALL_PIN[0]) / sizeof(BALL_PIN[16]); // Number of lines in the sensor array
        const int BALL_PIN[16] = {31, 29, 27, 25, 23, 19, 17, 15, 32, 34, 36, 38, 40, 42, 44, 46};
        const float BALL_Directions[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5}; // Direction of the ball 

};