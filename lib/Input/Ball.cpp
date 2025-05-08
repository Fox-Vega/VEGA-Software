#include <Ball.h>
#include <Input.h>

void BALL::setup() {
    for (int i = 0; i < NUMBalls; i++) {
        pinMode(Ball_PIN[i], INPUT);
    }
}

void BALL::read() {
    Max_BallValue = 0;
    Total_X = 0;
    Total_Y = 0;
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
    BallNumStart = Max_BallNum - 3;
    if (BallNumStart < 0) {
        BallNumStart += 16;
    }
    for (int i = BallNumStart; i < BallNumStart + 6; i++) {
        if (i > 15) {
            i -= 16;
        }
        myvector.get_cordinate(Ball_Directions[i], ball.get_value(i));
        Total_X += myvector.get_x();
        Total_Y += myvector.get_y();
    }
}

int BALL::get_value(short BallNum) { 
    Ball_Distance =  Ball_Values[BallNum] * BallDistance_offset;
    return Ball_Distance;
}

int BALL::get_distance() {
    return myvector.get_magnitude(Total_X, Total_Y);
}

int BALL::get_direction() {
    return myvector.get_azimuth(Total_X, Total_Y);
}
