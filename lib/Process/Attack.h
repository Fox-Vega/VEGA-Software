#include <Input.h>
#include <Output.h>

class Attack {
    public:
        void Attack_Setup();
        void Attack_BallApproach(int BallDirection, int BallDistance);
    private:
        // Adjustments
        const int BallApproach_radius = 100;
};