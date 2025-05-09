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
};
