#include <Arduino.h>

class MyVECTOR {
    public:
        void GetCordinate(float Azimuth, float Magnitude);
        int GetAzimuth(float X, float Y);
        int GetMagnitude(float X, float Y);
        int GetX();
        int GetY();
        
        int GetCordinate_flag;

    private:
        float X;
        float Y;
        float Theta;
        float Azimuth;
        float Magnitude;
};