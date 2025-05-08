#include <motor.h>
#include <API.h>
#include <Input.h>
#include <Output.h>


 //TODO もし姿勢制御が反対向きになっていた場合、motor.move の中の　+　-　を変更すること。
 //TODO もしモーターが逆回転していた場合、PIN1とPIN2の内容を反転させること。


void MOTOR::setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(motor_PIN1[i], OUTPUT);
        pinMode(motor_PIN2[i], OUTPUT);
    }
}

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

void MOTOR::free() {
    for (int i = 0; i < 4; i++) {
        analogWrite(motor_PIN1[i], 0);
        analogWrite(motor_PIN2[i], 0);
    }
}

void MOTOR::brake() {
    for (int i = 0; i < 4; i++) {
        analogWrite(motor_PIN1[i], 255);
        analogWrite(motor_PIN2[i], 255);
    }
}
