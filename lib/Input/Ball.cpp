#include <Ball.h>
#include <Input.h>

void BALL::setup() {
    for (int i = 0; i < NUMball; i++) {
        pinMode(ball_PINs[i], INPUT);
    }
}

void BALL::read() {
    max_ballvalue = 0;
    total_x = 0;
    total_y = 0;
    for (int i = 0; i < 16; i++) {
        ball_values[i] = 0;
    }
    for (int j = 0; j < 60; j++) {
        for (int i = 0; i < NUMBall; i++) {
            if (digitalRead(ball_PINs[i]) == HIGH) {
                ball_values[i] = ball_values[i] + 1;
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
        if (i >= NUMBalls) {
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

int BALL::get_magnitude() {
    return myvector.get_magnitude(Total_X, Total_Y);
}

int BALL::get_azimuth() {
    return myvector.get_azimuth(Total_X, Total_Y);
}
