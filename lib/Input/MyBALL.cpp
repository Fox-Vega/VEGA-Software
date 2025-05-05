#include <MyBALL.h>
#include <Input.h>

void MyBALL::MyBALL_Setup() {
    for (int i = 0; i < NUMBALLS; i++) {
        pinMode(BALL_PIN[i], INPUT);
    }
}

int MyBALL::MyBALL_Read() {
    Max_BALLValue = 0;
    for (int i = 0; i < 16; i++) {
        BALL_Values[i] = 0;
    }
    for (int j = 0; j < 60; j++) {
        for (int i = 0; i < NUMBALLS; i++) {
            if (digitalRead(BALL_PIN[i]) == HIGH) {
                BALL_Values[i] = BALL_Values[i] + 1;
            }
        }
    }
    for (int i = 0; i < NUMBALLS; i++) {
        if (BALL_Values[i] > Max_BALLValue) {
            Max_BALLValue = BALL_Values[i];
            Max_BALLNum = i;
        }
    }
}

int MyBALL::Get_BALLDistance() {
    BALL_Distance = Max_BALLValue * BALLDistance_offset;
    return BALL_Distance;
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