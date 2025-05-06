#include <Line.h>
#include <Input.h>



// 草塩からの伝言
// 
// コメントはほとんどAIをに書かせてます（意味の修正はちゃんとしてるからね）
// 最初にふざけて書いたせいでこの有り様です
// 
// 
// 
// 
// 
// 
// 
// 


// めも
// （消すなよ？）
// 
// ２つの反応が強いラインの位置関係から角度と距離を計算し
// 戻り値として返す(ベクトル使うかも？)
// 
// ディフェンス用にライントレースの状態をcharで返す
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 


int line_deg_list_24[24] = {0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255, 270, 285, 300, 315, 330, 345};
//ラインセンサのもともとの角度だぁ
int line_memory[24][2] = {//ラインセンサの値を格納するよぉ
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 10}, {5, 20}, {6, 30}, {7, 50},
    {8, 30}, {9, 20}, {10, 10}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0},
    {16, 0}, {17, 0}, {18, 0}, {19, 0}, {20, 0}, {21, 0}, {22, 0}, {23, 0},
    {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 10}, {5, 20}, {6, 30}, {7, 50},
    {8, 30}, {9, 20}, {10, 10}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0},
    {16, 0}, {17, 0}, {18, 0}, {19, 0}, {20, 0}, {21, 0}, {22, 0}, {23, 0}};
int binaryNum[8][3] = {//マルチプレクサぁ
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1},
};

void LINE::Line_Setup()//ピン設定とかぁ
{
    pinMode(selectA, OUTPUT);
    pinMode(selectB, OUTPUT);
    pinMode(selectC, OUTPUT);
    pinMode(readPin1, INPUT);
    pinMode(readPin2, INPUT);
    pinMode(readPin3, INPUT);
}

int LINE::Read_Line(char mode)//呼び出しぃ
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


int LINE::case1()//ケースわん！（ラインの角度と距離を算出）
{
    Line_Read();
    Line_buble_sort();
}

int LINE::case2()//ケースつー！（ディフェンス用）
{
    Line_Read();
    Line_buble_sort();
}




int LINE::Line_Read()//マルチプレクサぁ　使って　ラインセンサの値を取得するよぉ
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
        line_memory[i][1] = analogRead(readPin1)*(100/1024);
        line_memory[i + 8][1] = analogRead(readPin2)*(100/1024);
        line_memory[i + 16][1] = analogRead(readPin3)*(100/1024);
    }
    return 0; 
}

void LINE::Line_buble_sort()//バブルソートでラインセンサの値をソートするよぉ
// これでラインセンサの値が大きい順に並ぶよぉ
{
    int temp[2];//一時保存用の変数だぁ
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