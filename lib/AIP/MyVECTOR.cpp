#include <MyVECTOR.h>

void MyVECTOR::get_cor(float Azimuth, float Magnitude) {
    Theta = 90 - Azimuth;
    if (Theta < -180) {
        Theta += 360;
    } else if (Theta > 180) {
        Theta -= 360;
    }
    x = float(cos(radians(Theta)) * Magnitude);
    y = float(sin(radians(Theta)) * Magnitude);
}

void MyVECTOR::get_ppcord(Pl_x, Pl_y, Po_x, Po_y) {
    Ps_x = float(abs(Po_x - Pl_x));
    Ps_y = float(abs(Po_y - Po_y));
    if (Po_x < Pl_x) {
        Ps_x = Ps_x - (Ps_x * 2);
    } else if (Po_y < Pl_y) {
        Ps_y = Ps_y - (Ps_y * 2);
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
    return Ps_x;
}

int MyVECTOR::get_psy() {
    return Ps_y;
}
