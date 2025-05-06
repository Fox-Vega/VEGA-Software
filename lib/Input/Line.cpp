#include <Line.h>
#include <Input.h>

// TODOリスト
// 
// 2つの反応が強いラインセンサの位置関係から角度と距離を計算し、
// 戻り値として返す（ベクトル使うかも）
// 
// ディフェンス用にライントレースの状態をchar型で返す
// 

void LINE::Line_Setup() // ピンの設定を行う
{
    pinMode(selectA, OUTPUT);
    pinMode(selectB, OUTPUT);
    pinMode(selectC, OUTPUT);
    pinMode(readPin1, INPUT);
    pinMode(readPin2, INPUT);
    pinMode(readPin3, INPUT);
}

int LINE::Read_Line(char mode) // ラインセンサの読み取りモードを選択
{
    switch(mode)
    {
        case 'a':
            case1();
            break;
        case 'b':
            case2();
            break;
    }
}

int LINE::case1() // けーす１ラインセンサの角度と距離を計算
{
    Line_Read();
    Line_buble_sort();
    int line_two[2] = {0, 0}; // 反応が強いラインセンサの番号を格納
}

int LINE::case2() // けーす２ディフェンス用の処理
{
    Line_Read();
    Line_buble_sort();
}

int LINE::Line_Read() // マルチプレクサを使用してラインセンサの値を取得
{
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

void LINE::Line_buble_sort() // バブルソートでラインセンサの値を昇順に並び替える
{
    int temp[2]; // バブルソートの一時保存用の変数
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