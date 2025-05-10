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
        mypixel.brightness(100);
        switch (phase) {
            case 1:
                if (switch_pressed == 1){
                    mode = 1;
                    phase = 2;
                    mypixel.clear();
                    mypixel.multis(1, 16, 255, 0, 0);
                    mybuzzer.start(200, 4);
                    break;
                } else if (switch_pressed == 2) {
                    mode = 2;
                    phase = 2;
                    mypixel.clear();
                    mypixel.multis(1, 16, 0, 0, 255);
                    mybuzzer.start(200, 4);
                    break;
                } else if (switch_pressed == 3) {
                    mode = 3;
                    phase = 2;
                    mypixel.clear();
                    mypixel.multis(1, 16, 255, 0, 255);
                    mybuzzer.start(200, 4);
                    break;
                }
            
            case 2:
                if (switch_pressed == 1){
                    phase = 1;
                    mybuzzer.start(100, 4);
                    break;
                } else if (switch_pressed == 2) {
                    if (startcord < 4) {
                        startcord += 1;
                    }
                    mypixel.clear();
                    gyro.cord_custom(startcords_x[startcord], startcords_y[startcord]);
                    mypixel.unis(startPIXELs[startcord], 255, 0, 0);
                    mybuzzer.start(300, 4);
                    delay(100);
                    mybuzzer.start(300, 4);
                    break;
                } else if (switch_pressed == 3) {
                    phase = 3;
                    mybuzzer.start(200, 4);
                    break;
                }
            case 3:
                if (switch_pressed == 1){
                    phase = 2;
                    mybuzzer.start(100, 4);
                    break;
                } else if (switch_pressed == 2) {
                    gyro.dir_reset();
                    mybuzzer.start(200, 2);
                    delay(100);
                    mybuzzer.start(100, 4);
                    break;
                } else if (switch_pressed == 3) {
                    gyro.cord_custom(startcords_x[startcord], startcords_y[startcord]);
                    mybuzzer.start(300, 4);
                    delay(100);
                    mybuzzer.start(300, 4);
                    break;
                } else if (toggle_stat == 1) {
                    Run = true;
                } else {
                    mybuzzer.start(300, 8);
                    delay(100);
                }
        }
    }
    mypixel.brightness(999);
    return Run;
}

int General::check_run() {
    if (myswitch.check_toggle() == 0) {
        Run = false;
    } else {
        Run = true; 
    }
    return Run;
}

int General::check_mode() {
    return mode;
}

void General::update() {
    gyro.get_cord();
}


int General::calculate_deg(char mode, int num1, int num2) {//角度計算
    int r=999;//リターン（初期値はエラー用）
    if(mode == 'A')//加算（slow）
    {//1度ずつ加算してそのたびに360以上になってないか確認
        for(int i=0;i<num2;i++){
            if(num1 == 360){
                num1 = 0;
            }
            else{
                num1++;
            }
            r = num1;
        }
    }
    else if(mode == 'a')//加算（fast）
    {//一気に加算して360以上になってたら360で割った余りを返す（間違ってたら勝手に書いといていいよ）
        num1 = num1 + num2;
        if(num1>360){
            num1 = num1%360;
        }
        r = num1;
    }
    else if(mode='S')//減算（slow）
    {//1度ずつ減算してそのたびに0以下になってないか確認
        for(int i=0;i<num2;i++){
            if(num1 == 0){
                num1 = 360;
            }
            else{
                num1--;
            }
            r = num1;
        }
    }
    else if(mode='R')//反転（only fast）
    {//num1を180度回転　　180にnum1を引いた絶対値を返す
        r=abs(180 - num1);
        r = num1;
    }
    else if(mode='s')//減算（fast）
    {//一気に減算して0以下になってたら360で割った余りを返す（間違ってたら勝手に書いといていいよ）
        num1 = num1 - num2;
        if(num1<0){
            num1 = (num1+360)%360;
        }
        r = num1;
    }
    return r;
}

int General::cal_d(char mode, int num1, int num2)
{
    return calculate_deg(mode, num1, num2);
}