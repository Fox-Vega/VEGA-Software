#include <Arduino.h>

class MySWITCH {
    public:
        void setup();
        int check_tact();//タクトスイッチの状態を確認（右側が優先）
        int check_toggle();//トグルスイッチの状態を確認

    private:
        const short tactswitchPIN[3] = {12, 35, 33};
        const short toggleswitchPIN = 10;
        short pushed_tact;
        short toggle_stat = 0;
};
