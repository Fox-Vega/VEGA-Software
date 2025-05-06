#include <Ball.h>
#include <Input.h>

void BALL::Ball_Setup() {
    for (int i = 0; i < NUMBalls; i++) {
        pinMode(Ball_PIN[i], INPUT);
    }
}

void BALL::Ball_Read() {
    Max_BallValue = 0;
    for (int i = 0; i < 16; i++) {
        Ball_Values[i] = 0;
    }
    for (int j = 0; j < 60; j++) {
        for (int i = 0; i < NUMBalls; i++) {
            if (digitalRead(Ball_PIN[i]) == HIGH) {
                Ball_Values[i] = Ball_Values[i] + 1;
            }
        }
    }
    for (int i = 0; i < NUMBalls; i++) {
        if (Ball_Values[i] > Max_BallValue) {
            Max_BallValue = Ball_Values[i];
            Max_BallNum = i;
        }
    }
}

int BALL::Get_BallDistance(short BallNum) { 
    Ball_Distance =  Ball_Values[BallNum] * BallDistance_offset;
    return Ball_Distance;
}

int BALL::Get_BallDirection() {
    Total_X = 0;
    Total_Y = 0;
    BallNumStart = Max_BallNum - 3;
    if (BallNumStart < 0) {
        BallNumStart += 16;
    }
    myball.MyBALL_Read();
    for (int i = BallNumStart; i < BallNumStart + 6; i++) {
        myvector.GetCordinate(Ball_Directions[i], myball.Get_BallDistance(i));
        Total_X += myvector.GetX();
        Total_Y += myvector.GetY();
    }
    return myvector.GetAzimuth(Total_X, Total_Y);
}