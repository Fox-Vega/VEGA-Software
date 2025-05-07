#include <motor.h>
#include <API.h>
#include <Input.h>
#include <Output.h>

 //TODO もし姿勢制御が反対向きになっていた場合、motor.move の中の　+　-　を変更すること。

void MOTOR::move(int Movement_Azimuth, int Power_, int Direction_Azimuth) {
    difix_PWM = motor.difix(Direction_Azimuth) / 2; //PWM値に変換された補正値を取得
    for (int i = 0; i < 4; i++) {
        Azimuth_motor = Movement_Azimuth - motor_degrees[i];//オムニの軸がy軸になるようにする
        myvector.get_cordinate(Azimuth_motor, Power_ - difix_PWM);
        Power = myvector.get_x();
        if (Power >= 0) {
            PoMi = true;
        } else {
            PoMi = false;
        }
        if (PoMi == true) {
            motor_PWM1[i] = Power += difix_PWM;
            motor_PWM2[i] = 0;
        } else {
            motor_PWM1[i] = 0;
            motor_PWM2[i] = Power -= difix_PWM;
        }
    }
}

double MOTOR::difix(double setpoint){
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

int MOTOR::difix_getPoMi() {
    return difix_PoMi;
}

void MOTOR::brake() {
    for (int i = 0; i < 4; i++) {
        analogWrite(motor_PIN1[i], 255);
        analogWrite(motor_PIN2[i], 255);
    }
}