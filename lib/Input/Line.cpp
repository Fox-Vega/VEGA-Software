#include <Line.h>
#include <Input.h>


#define lineDetect 5
//AI学習用↓　　　（これで学習できるのかはわからん）
/*
RCJJのロボットのラインセンサ（エンジェルリング（円型））の角度を出したりするプログラム
センサの数は24個
基本時計回りで処理
https://note.com/shiokara_rcj/n/n44bbd2454c07　←参考
999はエラー用

*/

// TODO
//2つの反応が強いラインセンサの位置関係から角度と距離を計算し、戻り値として返す（ベクトル使うかも）
// ディフェンス用にライントレースの状態をchar型で返す

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

int LINE::get_line() {
    line.read();
    line.get_line_deg();
}

int LINE::read(){ //読み取りを24かいを三回繰り返して当たっていたら配列に１足して　２以上でboolをtrue
    int line_value [24]={0};
    for(int i = 0; i < 8; i++){//i8
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        if(analogRead(readPin1) > lineDetect){
            line_value[i]++;
        }
    }
    for(int i = 8; i < 16; i++){
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        if(analogRead(readPin2) > lineDetect){
            line_value[i]++;
        }
    }
    for(int i = 16; i < 24; i++){
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        if(analogRead(readPin3) > lineDetect){
            line_value[i]++;
        }
    }
}



// void LINE::bubble_sort() {
//     for (int i = 0; i < NUMLines - 1; i++) {
//         for (int j = 0; j < NUMLines - i - 1; j++) {
//             if (Line_memory[j][1] > Line_memory[j + 1][1]) {
//                 for (int k = 0; k < 2; k++) {
//                     temp[k] = Line_memory[j][k];
//                     Line_memory[j][k] = Line_memory[j + 1][k];
//                     Line_memory[j + 1][k] = temp[k];
//                 }
//             }
//         }
//     }
// }

int get_line_deg() {
    count =0;
    for(int i = 0; i < NUMLines; i++) {
        if (linebooooool[i] == true) {
            if(linebooooool[i+1] == true) {
                i++;
                add_line_deg(i,i+1);
            }
            else {
                add_line_deg(i,999);
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

void add_line_deg(int num,int num2) {
    if(num2 == 999){//999はエラー用
        line_detect[count] = line_deg_list_24[num];
    }
    else{
        line_detect[count] =  (line_deg_list_24[num]+line_deg_list_24[num2])/2;
    }
    count++;
}