#include <Arduino.h>

class MyLINE {
    public:
        void MyLINE_Start();
        void MyLINE_End();

    private:
        int LINE_PIN[1] = {2}; // Pin where the line sensor is connected
};