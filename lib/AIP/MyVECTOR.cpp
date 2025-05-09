#include <MyVECTOR.h>

void MyVECTOR::get_cordinate(float Azimuth, float Magnitude) {
    Theta = 90 - Azimuth;
    if (Theta < -180) {
        Theta += 360;
    } else if (Theta > 180) {
        Theta -= 360;
    }
    x = float(cos(radians(Theta)) * Magnitude);
    y = float(sin(radians(Theta)) * Magnitude);
}

void MyVECTOR::get_ppcordinate(Pl_X, Pl_Y, Po_X, Po_Y) {
    Ps_X = float(abs(Po_X - Pl_X));
    Ps_Y = float(abs(Po_Y - Po_Y));
    if (Po_X < Pl_X) {
        Ps_X = Ps_X - (Ps_X * 2);
    } else if (Po_Y < Pl_Y) {
        Ps_Y = Ps_Y - (Ps_Y * 2);
    }
}

int MyVECTOR::get_azimuth(float x, float y) {
    Theta = atan2(y, x);
    Azimuth = float(90 - degrees(Theta));
    if (Azimuth < 0) { 
        Azimuth += 360;
    } else if (Azimuth > 360) {
        Azimuth -= 360;
    }
    return Azimuth;
}

int MyVECTOR::get_magnitude(float x, float y) {
    return float(sqrt(x * x + y * y));
}

int MyVECTOR::get_x() {
    return x;
}

int MyVECTOR::get_y() {
    return y;
}

int MyVECTOR::get_psx() {
    return Ps_X;
}

int MyVECTOR::get_psy() {
    return Ps_Y;
}
