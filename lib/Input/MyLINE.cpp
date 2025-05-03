#include <MyLINE.h>
#include <Arduino.h>

#define true 1
#define false 0

const int line_positions[24]={0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255, 270, 285, 300, 315, 330, 345};

void MyLINE::MyLINE_Setup() {
    // for (int i = 0; i < NUMLINES; i++) {
    //     pinMode(LINE_PIN[i], INPUT); // Set each line sensor pin as input
    // }
};

int MyLINE::Read_LINE(){
};

int MyLINE::Line_Read(){
};