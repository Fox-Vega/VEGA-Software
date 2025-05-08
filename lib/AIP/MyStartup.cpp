#include <Input.h>
#include <Output.h>

void MySetup() {
    ball.setup();
    gyro.setup();
    line.setup();
    motor.setup();
    mypixel.setup();
    mybuzzer.setup();
    Serial.begin(9600);
}
