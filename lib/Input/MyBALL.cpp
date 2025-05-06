#include <MyBALL.h>
#include <Input.h>

void MyBALL::MyBALL_Setup() {
    for (int i = 0; i < NUMBALLS; i++) {
        pinMode(BALL_PIN[i], INPUT);
    }
}

void MyBALL::MyBALL_Read() {
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

int MyBALL::Get_BALLDistance(short BallNum) { 
    BALL_Distance =  BALL_Values[BallNum] * BALLDistance_offset;
    return BALL_Distance;
}

int MyBALL::Get_BALLDirection() {
    Total_X = 0;
    Total_Y = 0;
    BALLNumStart = Max_BALLNum - 3;
    if (BALLNumStart < 0) {
        BALLNumStart += 16;
    }
    myball.MyBALL_Read();
    for (int i = BALLNumStart; i < BALLNumStart + 6; i++) {
        myvector.GetCordinate(BALL_Directions[i], myball.Get_BALLDistance(i));
        Total_X += myvector.GetX();
        Total_Y += myvector.GetY();
    }
    return myvector.GetAzimuth(Total_X, Total_Y);
}