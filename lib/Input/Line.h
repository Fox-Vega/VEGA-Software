#include <Arduino.h>

class LINE {
    public:
        void Line_Setup();//セットアップ関数ぅ
        void Line_End();//終了関数ぅ
        int Read_Line(char mode);//呼び出し関数ぅ
        int Line_Read();
        void Line_buble_sort(); //バブルソートするぞぉ
        int case1();//ケースわん！（ラインの角度と距離を算出）
        int case2();//ケースつー！（ディフェンス用）
        int case3();//ケースすりぃ！（まだ使ってない）
        int case4();//ケースふぉぉ！（まだ使ってない）
    private:
        #define true 1 //true
        #define false 0 //false
        #define NUMLINES 24 // Number of line sensors
        #define readPin1 A13 // Pin for reading the first line sensor
        #define readPin2 A11 // Pin for reading the second line sensor
        #define readPin3 A9 // Pin for reading the third line sensor
        
        const int selectA = 22;
        const int selectB = 24;
        const int selectC = 26;
        int line_deg;
};