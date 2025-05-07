#include <motor.h>
#include <API.h>

void MOTOR::move(int Azimuth, int Power_) {
    for (int i = 0; i < 4; i++) {
        AzimuthM = Azimuth - motor_degrees[i];//オムニの軸がy軸になるようにする
        myvector.get_cordinate(AzimuthM, Power_);
        Power = myvector.get_x();
        if (Power < 0) {
            PoMi = false;
        } else {
            PoMi = true;
        }
        if (PoMi == true) {
            analogWrite(motor_PIN1[i], Power);
            analogWrite(motor_PIN2[i], 0);
        } else {
            analogWrite(motor_PIN1[i], 0);
            analogWrite(motor_PIN2[i], Power);
        }
    }
}