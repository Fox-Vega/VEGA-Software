#include <Startup.h>
#include <Input.h>
#include <Output.h>

void Startup::setup() {
    ball.setup();
    gyro.setup();
    line.setup();
    motor.setup();
    mypixel.setup();
    mybuzzer.setup();
    Serial.begin(9600);
}

void Start::startup() {
    mode = 1;
    phase = 1;
    while(phase != 4){
        switch (phase) {
            case 1:
                switch_pressed = switch.check_tact();
                if (switch_pressed == 1){
                } else if () {
                }
                
        }
    }
        
}
