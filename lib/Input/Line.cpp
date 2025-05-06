#include <Line.h>
#include <Input.h>

int line_deg_list_24[24]={0,15,30,45,60,75,90,105,120,135,150,165,180,195,210,225,240,255,270,285,300,315,330,345};
int line_memory[24][2]={
    {0,0},{1,0},{2,0},{3,0},{4,10},{5,20},{6,30},{7,50},
    {8,30},{9,20},{10,10},{11,0},{12,0},{13,0},{14,0},{15,0},
    {16,0},{17,0},{18,0},{19,0},{20,0},{21,0},{22,0},{23,0}
};
int binaryNum[8][3]={
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1},
};

void LINE::Line_Setup()
{
    pinMode(selectA,OUTPUT);
    pinMode(selectB,OUTPUT);
    pinMode(selectC,OUTPUT);
    pinMode(readPin1,INPUT);
    pinMode(readPin2,INPUT);
    pinMode(readPin3,INPUT);
};

int LINE::Read_Line()
{
    //Line_Read();
    line.Line_buble_sort();
    line_deg=line_deg_list_24[line_memory[0][0]];
    printf("%d",line_deg);
};

int LINE::Line_Read()
{
    //マルチプレクサわからん 追記：理解した
    for(int i=0;i<8;i++){
        line_memory[i][0]=i;
        line_memory[i+8][0]=i+8;
        line_memory[i+16][0]=i+16;
        digitalWrite(selectA,binaryNum[i][0]);
        digitalWrite(selectB,binaryNum[i][1]);
        digitalWrite(selectC,binaryNum[i][2]);
        delay(1);
        line_memory[i][1]=analogRead(readPin1);
        line_memory[i+8][1]=analogRead(readPin2);
        line_memory[i+16][1]=analogRead(readPin3);
    }
};

void LINE::Line_buble_sort()
{
    int temp[3];
    for (int i = 0; i < 24 - 1; i++) {
        for (int j = 0; j < 24 - i - 1; j++) {
            if (line_memory[1][j] > line_memory[1][j + 1]) {
                for (int k = 0; k < 3; k++) {
                    temp[k] = line_memory[k][j];
                    line_memory[k][j] = line_memory[k][j + 1];
                    line_memory[k][j + 1] = temp[k];
                }
            }
        }
    }
}