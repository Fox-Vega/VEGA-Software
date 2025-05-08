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

int Startup::startup() {
    phase = 1;
    while(phase != 4){
        switch_pressed = myswitch.check_tact();
        toggle_stat = myswitch.check_toggle();
        switch (phase) {
            case 1:
                if (switch_pressed == 1){
                    mode = 1;
                    phase = 2;
                    break;
                } else if (switch_pressed == 2) {
                    mode = 2;
                    phase = 2;
                    break;
                } else if (switch_pressed == 3) {
                    mode = 3;
                    phase = 2;
                    break;
                }
            
            case 2:
                if (switch_pressed == 1){
                    phase = 1;
                    break;
                } else if (switch_pressed == 2) {
                    break;
                } else if (switch_pressed == 3) {
                    phase = 3;
                    break;
                }
            case 3:
                if (switch_pressed == 1){
                    phase = 2;
                    break;
                } else if (switch_pressed == 2) {
                    gyro.dir_reset();
                    break;
                } else if (switch_pressed == 3) {
                    gyro.pos_reset();
                    break;
                } else if (toggle_stat == 1) {
                    Run_p = true;
                }
        }
    }
    return Run_p;
}

int Startup::check_run() {
    if (myswitch.check_toggle() == 0) {
        Run_p = false;
    }
    return Run_p;
}