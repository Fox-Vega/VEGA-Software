#include <Arduino.h>

class SWITCH() {
    public:
        setup();
        check_tact();
        check_toggle();

    private:
        tactswitchPIN[3] = {1, 1, 1};
        toggleswitchPIN = 1;
}
