#include <MyVECTOR.h>

void MyVECTOR::get_cordinate(float Azimuth, float Magnitude) {
    Theta = 90 - Azimuth;
    if (Theta < -180) {
        Theta += 360;
    } else if (Theta > 180) {
        Theta -= 360;
    }
    x = cos(radians(Theta)) * Magnitude;
    y = sin(radians(Theta)) * Magnitude;
}

int MyVECTOR::get_azimuth(float x, float y) {
    Theta = atan2(y, x);
    Azimuth = 90 - degrees(Theta);
    if (Azimuth < 0) { 
        Azimuth += 360;
    } else if (Azimuth > 360) {
        Azimuth -= 360;
    }
    return Azimuth;
}

int MyVECTOR::get_magnitude(float x, float y) {
    return sqrt(x * x + y * y);
}

int MyVECTOR::get_x() {
    return x;
}

int MyVECTOR::get_y() {
    return y;
}
