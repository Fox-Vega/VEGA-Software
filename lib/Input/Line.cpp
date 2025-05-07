#include <Line.h>
#include <Input.h>


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
    line.bubble_sort();
}

int LINE::read() {
    for (int i = 0; i < 8; i++) {
        Line_memory[i][0] = i;
        Line_memory[i + 8][0] = i + 8;
        Line_memory[i + 16][0] = i + 16;
        digitalWrite(selectA, BinaryNum[i][0]);
        digitalWrite(selectB, BinaryNum[i][1]);
        digitalWrite(selectC, BinaryNum[i][2]);
        delay(1);
        Line_memory[i][1] = analogRead(readPin1) * (100 / 1024);
        Line_memory[i + 8][1] = analogRead(readPin2) * (100 / 1024);
        Line_memory[i + 16][1] = analogRead(readPin3) * (100 / 1024);
    }
    return 0; 
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
