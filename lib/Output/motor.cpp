#include <motor.h>
#include <API.h>
#include <Input.h>
#include <Output.h>


 //TODO もし姿勢制御が反対向きになっていた場合、motor.move の中の　+　-　を変更すること。
 //TODO もしモーターが逆回転していた場合、PIN1とPIN2の内容を反転させること。


void MyMOTOR::setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(motor_PIN1[i], OUTPUT);
        pinMode(motor_PIN2[i], OUTPUT);
    }
}

void MyMOTOR::run(float Movement_Azimuth, int Power_, int Dir_Azimuth) {
    difix_PWM = mymotor.difix(Dir_Azimuth) / 2;
    for (int i = 0; i < 4; i++) {
        Azimuth_motor = Movement_Azimuth - motor_degrees[i];//オムニの軸がy軸になるようにする
        myvector.get_cord(Azimuth_motor, Power_ - abs(difix_PWM));
        Power = myvector.get_x();
        if (Power >= 0) {
            PoMi = true;
        } else {
            PoMi = false;
            Power -= (Power * 2);
        }
        if (PoMi == true) {
            analogWrite(motor_PIN1[i], 0);
            analogWrite(motor_PIN2[i], Power -= difix_PWM);
        } else {
            analogWrite(motor_PIN1[i], Power += difix_PWM);
            analogWrite(motor_PIN2[i], 0);
        }
    }
}

int MyMOTOR::difix(int setpoint) {
    double error = setpoint - gyro.get_azimuth();
    integral += error;
    derivative = error - prev_error;
    prev_error = error;
    double angularVelocity = kp * error + ki * integral + kd * derivative;
    if (angularVelocity >= 0) {
        difix_PoMi = true;
    } else {
        difix_PoMi = false;
    }
    return motorPWM = int(constrain(abs(angularVelocity) * pwmScale, 0, 255));
}

void MyMOTOR::free() {
    for (int i = 0; i < 4; i++) {
        analogWrite(motor_PIN1[i], 0);
        analogWrite(motor_PIN2[i], 0);
    }
}

void MyMOTOR::brake() {
    for (int i = 0; i < 4; i++) {
        analogWrite(motor_PIN1[i], 255);
        analogWrite(motor_PIN2[i], 255);
    }
}
