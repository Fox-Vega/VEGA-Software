#include <Arduino.h>
#include <stdio.h>
#include <MyPIXEL.h>
#include "Output.h"


void setup() {
    Serial.begin(9600);
    mypixel.MyPIXEL_Setup();
}
    
void loop() {
    mybuzzer.MyBUZZER_Preset(1); // Start the buzzer with a note and duration
    mypixel.MyPIXEL_Multi(1, 5, 255, 0, 0);
}