#include <MyVECTOR.h>

void MyVECTOR::get_cord(float azimuth, float magnitude) {
    theta = 90 - azimuth;
    if (theta < -180) {
        theta += 360;
    } else if (theta > 180) {
        theta -= 360;
    }
    x = float(cos(radians(theta)) * magnitude);
    y = float(sin(radians(theta)) * magnitude);
}

void MyVECTOR::get_ppcord(float pl_x, float pl_y, float po_x, float po_y) {
    ps_x = float(abs(po_x - pl_x));
    ps_y = float(abs(po_y - po_y));
    if (po_x < pl_x) {
        ps_x = ps_x - (ps_x * 2);
    } else if (po_y < pl_y) {
        ps_y = ps_y - (ps_y * 2);
    }
}

int MyVECTOR::get_azimuth(float x, float y) {
    theta = atan2(y, x);
    azimuth = float(90 - degrees(theta));
    if (azimuth < 0) { 
        azimuth += 360;
    } else if (azimuth > 360) {
        azimuth -= 360;
    }
    return azimuth;
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
    return ps_x;
}

int MyVECTOR::get_psy() {
    return ps_y;
}
