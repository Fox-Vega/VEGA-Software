#pragma once
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class LINE {
    public:
        //呼び出し可能
        void setup(); // ピン設定を行うセットアップ関数
        void end(); // 終了処理用の関数（未実装、用途未定)
        int get_line(); // ラインセンサの値を取得する関数＞＞＞呼び出し＜＜＜
        int calculate_deg(char mode, int num1, int num2);//角度計算
        int calc_d(char mode, int num1, int num2);//上の略
        //不可能（多分バグる）
        int read(); // ラインセンサの値を取得する関数
        int get_linedeg(); // ラインセンサの角度を取得する関数
        void add_linedeg(int num,int num2); // ラインセンサの角度を追加する関数
    private:
        #define true 1
        #define false 0
        #define NUMLines 24
        int temp[2]; // バブルソートの一時保存用変数

        // マルチプレクサのアナログ入力ピン
        #define readPin1 A13
        #define readPin2 A11
        #define readPin3 A9
        
        // マルチプレクサのセレクトピン
        const int selectA = 22;
        const int selectB = 24;
        const int selectC = 26;

        int Line_deg; // ラインセンサの角度（戻り値用に使用する可能性あり）
        int Line_dis; // ラインセンサの距離（戻り値用に使用する可能性あり）

        // ラインセンサの角度（センサ番号と角度の対応）
        const int Line_deg_list_24[24] = {0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255, 270, 285, 300, 315, 330, 345};

        // ラインセンサの値を格納する2次元配列（センサ番号と値を保持）
        int Line_memory[24][2] = {
            {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 10}, {5, 20}, {6, 30}, {7, 50},
            {8, 30}, {9, 20}, {10, 10}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0},
            {16, 0}, {17, 0}, {18, 0}, {19, 0}, {20, 0}, {21, 0}, {22, 0}, {23, 0}};

        // マルチプレクサの設定値（二進数のリスト）
        int BinaryNum[24][3] = {
            {0, 0, 0},
            {0, 0, 1},
            {0, 1, 0},
            {0, 1, 1},
            {1, 0, 0},
            {1, 0, 1},
            {1, 1, 0},
            {1, 1, 1},
            {0, 0, 0},
            {0, 0, 1},
            {0, 1, 0},
            {0, 1, 1},
            {1, 0, 0},
            {1, 0, 1},
            {1, 1, 0},
            {1, 1, 1},
            {0, 0, 0},
            {0, 0, 1},
            {0, 1, 0},
            {0, 1, 1},
            {1, 0, 0},
            {1, 0, 1},
            {1, 1, 0},
            {1, 1, 1},
        };
        bool linebool[NUMLines]; // ラインセンサの状態を保持する配列
        int line_detect[4];
        int count = 0; // センサの状態を保存する時の場所の参照
};