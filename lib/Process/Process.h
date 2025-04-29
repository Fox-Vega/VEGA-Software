#include <Input.h>
#include <Output.h>

class PROCESS {
    public:
        void PROCESS_Setup();
        void PROCESS_BallApproach(int BallDirection, int BallDistance);
    private:
        // Adjustments
        const int BallApproach_radius = 100;
};