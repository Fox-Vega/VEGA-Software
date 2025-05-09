#include <MyVECTOR.h>

void MyVECTOR::get_cord(int azimuth, int magnitude) {
    theta = 90 - azimuth;
    if (theta < -180) {
        theta += 360;
    } else if (theta > 180) {
        theta -= 360;
    }
    x = int(cos(radians(theta)) * magnitude);
    y = int(sin(radians(theta)) * magnitude);
}

void MyVECTOR::get_ppcord(int pl_x, int pl_y, int po_x, int po_y) {
    ps_x = int(abs(po_x - pl_x));
    ps_y = int(abs(po_y - po_y));
    if (po_x < pl_x) {
        ps_x = ps_x - (ps_x * 2);
    } else if (po_y < pl_y) {
        ps_y = ps_y - (ps_y * 2);
    }
}

int MyVECTOR::get_azimuth(int x, int y) {
    theta = atan2(y, x);
    azimuth = int(90 - degrees(theta));
    if (azimuth < 0) { 
        azimuth += 360;
    } else if (azimuth > 360) {
        azimuth -= 360;
    }
    return azimuth;
}

int MyVECTOR::get_magnitude(int x, int y) {
    return int(sqrt(x * x + y * y));
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
