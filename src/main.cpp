#include <Arduino.h>
#include <AIP.h>
#include <Input.h>
#include <Output.h>

void setup() {
    general.setup();
    mybuzzer.preset(1);
    // general.startup();
}

void loop() {
    // int mode = general.check_mode();
    // gyro.get_cord();
    // if (general.check_run()) {
    //     switch (mode) {
    //     case 1:

    //     }
    // } else {
    //     mymotor.brake();
    // }
    gyro.get_cord();
    Serial.print(" ");
    Serial.print(gyro.get_x());
    Serial.print("  ");
    Serial.print(gyro.get_y());
    Serial.println("  ");
}
