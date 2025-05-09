#include <General.h>
#include <Input.h>
#include <Output.h>

void General::setup() {
    ball.setup();
    gyro.setup();
    line.setup();
    mymotor.setup();
    mypixel.setup();
    mybuzzer.setup();
    myswitch.setup();
    Serial.begin(9600);
}

int General::startup() {
    phase = 1;
    while(phase != 4){
        gyro.get_cord();
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
                    gyro.cord_reset();
                    break;
                } else if (toggle_stat == 1) {
                    Run_p = true;
                }
        }
    }
    return Run_p;
}

int General::check_run() {
    if (myswitch.check_toggle() == 0) {
        Run_p = false;
    } else {
       Run_p = true; 
    }
    return Run_p;
}

int General::check_mode() {
    return mode;
}

void General::update() {
    gyro.get_cord();
}
