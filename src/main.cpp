#include <Arduino.h>
#include <stdio.h>
#include <MyPIXEL.h>
#include "Output.h"

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    mybuzzer.MyBUZZER_Preset(1); // Start the buzzer with a note and duration
}
    
void loop() {
    mybuzzer.MyBUZZER_Preset(1); // Start the buzzer with a note and duration
}