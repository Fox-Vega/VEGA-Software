#include <Arduino.h>

class LINE {
    public:
        void Line_Setup();//セットアップ関数ぅ　（ピン設定とか）
        void Line_End();//終了関数ぅ　（まだ作ってないし何に使うのかもはっきりわかってない）
        int Read_Line(char mode);//呼び出し関数ぅ　（メインの呼び出しで使う）
        int Line_Read();
        void Line_buble_sort(); //バブルソートするぞぉ　（←その通り）
        int case1();//ケースわん！（ラインの角度と距離を算出）
        int case2();//ケースつー！（ディフェンス用）
        int case3();//ケースすりぃ！（まだ使ってない）
        int case4();//ケースふぉぉ！（まだ使ってない）
    private:
        #define true 1 //真！　（true）
        #define false 0 //偽！  (false)
        #define NUMLINES 24 // ラインセンサの数ぅ　（←そう、ラインの数）
        #define readPin1 A13 //　マルチプレクサぁ　の入力ピィン (マルチプレクサのアナログ入力ピン)
        #define readPin2 A11 // 　マルチプレクサぁ　の入力ピィン２　(マルチプレクサのアナログ入力ピン2)
        #define readPin3 A9 // 　マルチプレクサぁ　の入力ピィン３　(マルチプレクサのアナログ入力ピン3)
        
        const int selectA = 22;//　マルチプレクサぁ　のセレクトピィン　(マルチプレクサのセレクトピン1)
        const int selectB = 24;//　マルチプレクサぁ　のセレクトピィン２　(マルチプレクサのセレクトピン2)
        const int selectC = 26;//　マルチプレクサぁ　のセレクトピィン３　(マルチプレクサのセレクトピン3)
        int line_deg;//ラインの角度ぉ (角度　戻り値用に使うかも？)
        int line_dis;//ラインの距離ぃ　(距離　戻り値用に使うかも？)
};