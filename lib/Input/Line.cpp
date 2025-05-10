#include <Line.h>
#include <Input.h>


#define lineDetect 5


// TODO
// 
//2つの反応が強いラインセンサの位置関係から角度と距離を計算し、戻り値として返す（ベクトル使うかも）
// ディフェンス用にライントレースの状態をchar型で返す
//iPadでプッシュ
//
//
//
//りくは書くな　紛らわしい

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

int LINE::read(){ 
    for(int i = 0; i<NUMLines;i++){
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        int line_Averge =0;
        for(int j=0;j<10;j++){
            line_Averge += analogRead(readPin1);
        }
        line_Averge /= 10;
    }
    Line_memory[i][1] = line_Averge;
    linebooooool[i] = false;
    if (Line_memory[i][1] > lineDetect) {
        linebooooool[i] = true;
    }
}



void LINE::bubble_sort() {
    for (int i = 0; i < NUMLines - 1; i++) {
        for (int j = 0; j < NUMLines - i - 1; j++) {
            if (Line_memory[j][1] > Line_memory[j + 1][1]) {
                for (int k = 0; k < 2; k++) {
                    temp[k] = Line_memory[j][k];
                    Line_memory[j][k] = Line_memory[j + 1][k];
                    Line_memory[j + 1][k] = temp[k];
                }
            }
        }
    }
}

int get_line_deg() {
    int 
}
