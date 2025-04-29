#include <MyBALL.h>


void MyBALL::MyBALL_Setup() {
    for (int i = 0; i < NUMBALLS; i++) {
        pinMode(BALL_PIN[i], INPUT); // Set the pin mode to input for each ball sensor
    }
}

int MyBALL::MyBALL_Check() {
    for (int i = 0; i < 16; i++) {
        Detected_BALL[i] = 0;
    }
    for (int j = 0; j < 60; j++) { // Loop 60 times to check the ball sensors
        for (int i = 0; i < NUMBALLS; i++) {
            if (digitalRead(BALL_PIN[i]) == HIGH) { // Check if the ball is detected
                Detected_BALL[i] = Detected_BALL[i] + 1; // Increment the detected ball count
            }
        }
    }
}