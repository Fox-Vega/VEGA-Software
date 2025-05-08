#include <Arduino.h>
#include <API.h>
#include <Input.h>
#include <Output.h>

void setup() {
    general.setup();
    mybuzzer.preset(1);
    general.startup();
}

void loop() {
    const int mode = general.check_mode();
    if (general.check_run() == true) {
        switch (mode) {
            case 1:
                

        }
    }
}