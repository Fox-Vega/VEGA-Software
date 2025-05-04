#include <MyVECTOR.h>

void MyVECTOR::GetCordinate(float Azimuth, float Magnitude) {
    Theta = 90 - Azimuth;
    if (Theta < -180) {
        Theta += 360;
    } else if (Theta > 180) {
        Theta -= 360;
    }
    X = cos(Theta) * Magnitude;
    Y = sin(Theta) * Magnitude;
}

int MyVECTOR::GetAzimuth(float X, float Y) {
    Theta =  atan2(Y, X);
    Azimuth = 90 - Theta;
    if (Azimuth < 0) { 
        Azimuth += 360;
    } else if (Azimuth > 360) {
        Azimuth -= 360;
    }
    return Azimuth;
}

int MyVECTOR::GetMagnitude(float X, float Y) {
    return sqrt(X * X + Y * Y);
}

int MyVECTOR::GetX() {
    return X;
}

int MyVECTOR::GetY() {
    return Y;
}
