#include <Line.h>
#include <Input.h>


// TODO
// 
// 2つの反応が強いラインセンサの位置関係から角度と距離を計算し、
// 戻り値として返す（ベクトル使うかも）
// 
// ディフェンス用にライントレースの状態をchar型で返す

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
    line.buble_sort();
    int line_strong[2] = {0, 0};
}

int LINE::read() {
    for (int i = 0; i < 8; i++)
    {
        line_memory[i][0] = i;
        line_memory[i + 8][0] = i + 8;
        line_memory[i + 16][0] = i + 16;
        digitalWrite(selectA, binaryNum[i][0]);
        digitalWrite(selectB, binaryNum[i][1]);
        digitalWrite(selectC, binaryNum[i][2]);
        delay(1);
        line_memory[i][1] = analogRead(readPin1) * (100 / 1024);
        line_memory[i + 8][1] = analogRead(readPin2) * (100 / 1024);
        line_memory[i + 16][1] = analogRead(readPin3) * (100 / 1024);
    }
    return 0; 
}

void LINE::buble_sort() {
    int temp[2]; // バブルソートの一時保存用変数
    for (int i = 0; i < 24 - 1; i++)
    {
        for (int j = 0; j < 24 - i - 1; j++)
        {
            if (line_memory[j][1] > line_memory[j + 1][1]) 
            {
                for (int k = 0; k < 2; k++)
                {
                    temp[k] = line_memory[j][k];
                    line_memory[j][k] = line_memory[j + 1][k];
                    line_memory[j + 1][k] = temp[k];
                }
            }
        }
    }
}