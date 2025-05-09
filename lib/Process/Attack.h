#include <Input.h>
#include <Output.h>

class Attack {
    public:
        void attack();
        void b_p1();//ボールの回り込みパターン１
        void b_p2();//ボールの回り込みパターン２
        void b_p3();//ボールの回り込みパターン３
    private:
        // Adjustments
        const int BallApproach_radius = 100;//回り込み半径
        const int b_p1_deg = 10 //ボールの回り込みパターン１を行う範囲(片側)
        float appraoch_value = 1.5;//ボールの回り込みパターン１の際の角度増加値
        int b_p1approach_speed = 255;//ボールの回り込みパターン１の速度

        float approachdir;
};
