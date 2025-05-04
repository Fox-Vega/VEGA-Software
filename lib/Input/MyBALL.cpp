#include <MyBALL.h>
#include <Input.h>

void MyBALL::MyBALL_Setup() {
    for (int i = 0; i < NUMBALLS; i++) {
        pinMode(BALL_PIN[i], INPUT); // Set the pin mode to input for each ball sensor
    }
}

int MyBALL::MyBALL_Read() {
    Max_BALLValue = 0; // Reset the maximum ball value
    for (int i = 0; i < 16; i++) {
        BALL_Values[i] = 0; // Reset the ball values
    }
    for (int j = 0; j < 60; j++) { // Loop 60 times to check the ball sensors
        for (int i = 0; i < NUMBALLS; i++) {
            if (digitalRead(BALL_PIN[i]) == HIGH) { // Check if the ball is detected
                BALL_Values[i] = BALL_Values[i] + 1; // Increment the detected ball count
            }
        }
    }
    for (int i = 0; i < NUMBALLS; i++) {
        if (BALL_Values[i] > Max_BALLValue) {
            Max_BALLValue = BALL_Values[i]; // Update the maximum ball value
            Max_BALLNum = i; // Update the maximum ball pin number
        }
    }
}

int MyBALL::Get_BALLDistance() {
    BALL_Distance = Max_BALLValue * BALLDistance_offset;
    return BALL_Distance; // Return the distance of the ball
}

int MyBALL::Get_BALLDirection() {
    BALLNumStart = Max_BALLNum - 3;
    Total_X = 0;
    Total_Y = 0;
    if (BALLNumStart < 0) {
        BALLNumStart += 16;
    }
    for (int i = BALLNumStart; i < BALLNumStart + 6; i++) {
        myvector.GetCordinate(BALL_Directions[i], myball.Get_BALLDistance());
        Total_X += myvector.GetX();
        Total_Y += myvector.GetY();
    }
    myvector.GetAzimuth(Total_X, Total_Y);
}