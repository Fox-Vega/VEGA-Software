#include <Line.h>
#include <Input.h>
#include <Output.h>


#define lineDetect 5
/*
AI学習用↓　　　（一部はちゃんと学習できてるそう　でもリンクから内容取得はできないみたい）
RCJJのロボットのラインセンサ（エンジェルリング（円型））の角度を出したりするプログラム
センサの数は24個
基本時計回りで処理
https://note.com/shiokara_rcj/n/n44bbd2454c07　←参考
999はエラー用
neopixel 24個円型
*/

// TODO
// 
//距離を返す

//伝言
//りくはTODO書くな　邪魔だし紛らわしい　
//ARDUINOに入れるときに消すから勝手に消さないで　めっちゃ困る

void LINE::setup() {
    pinMode(selectA, OUTPUT);
    pinMode(selectB, OUTPUT);
    pinMode(selectC, OUTPUT);
    pinMode(readPin1, INPUT);
    pinMode(readPin2, INPUT);
    pinMode(readPin3, INPUT);
}

int LINE::get_azimuth() {
    line.read();
    return get_linedeg();
}

bool LINE::read(){ //読み取りを24かいを三回繰り返して当たっていたら配列に１足して　２以上でboolをtrue
    int line_value [24]={0};
    progress = 0;
    for(int i=0; i<3; i++){
    for(int i = 0; i < 8; i++){//i8
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        if(analogRead(readPin1) > lineDetect){
            line_value[i]++;
        }
        progress++;
    }
    for(int i = 8; i < 16; i++){
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        if(analogRead(readPin2) > lineDetect){
            line_value[i]++;
        }
        progress++;
    }
    for(int i = 16; i < 24; i++){
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        if(analogRead(readPin3) > lineDetect){
            line_value[i]++;
        }
            progress++;
    }
    bool line_bool =0;
    for(int i = 0; i < 24; i++){
        if(line_value[i] >= 2){
            line_status[i] = true;
            line_bool = 1;
        }
        else{
            line_status[i] = false;
        }
        progress++;
    }
    if(line_bool == 1){
        return true;
    }
    else{
        return false;
    }
}
}

int LINE::get_linedeg() {
    for(int i = 0; i < NUMLines; i++) {//初期化
        line_status[i] = false;
        line_detect[i] = 999;
    }
    count =0;
    for(int i = 0; i < NUMLines; i++) {
        if (line_status[i] == true) {
            if(line_status[i+1] == true) {
                i++;
                add_linedeg(i,i+1);
            }
            else {
                add_linedeg(i,999);
            }
        }
    }
    if(count == 0) {
        return 999;
    }
    else if(count == 1) {
        return line_detect[0];
    }
    else if(count == 2) {
        return (line_detect[0] + line_detect[1]) / 2;
    }
    else if(count == 3) {//3から先は後で書く　今は適当に前のコードのコピペみたいな
        return (line_detect[0] + line_detect[1] + line_detect[2]) / 3;
    }
    else if(count == 4) {
        return (line_detect[0] + line_detect[1] + line_detect[2] + line_detect[3]) / 4;
    }
}

void LINE::add_linedeg(int num,int num2) {
    if(num2 == 999){//999はエラー用
        line_detect[count] = Line_deg_list_24[num];
    }
    else{
        line_detect[count] =  (Line_deg_list_24[num]+Line_deg_list_24[num2])/2;
    }
    count++;
}

void LINE::print_pizel() {//neopixelの表示　　AIへ、「モニターではない！！」
    mypixel.clear();
    mypixel.brightness(999);
    for(int i=0; i<5; i++){
        if(line_detect[i] == 999){
            mypixel.closest(line_detect[i], 0, 255, 225);
        }
    }
    mypixel.closest(get_linedeg(), 255, 130, 0);
}

