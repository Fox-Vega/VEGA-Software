#include <Attack.h>

void Attack::attack() {
    if (line.read() == true) {
       
    } else {
        ball.read();
        ball_dir = ball.get_direction();
        if (ball_dir < b_p1_deg || ball_dir > 360 - b_p1_deg) {
            attack.b_p1();
        } else if (ball.get_distance > BallApproach_radius) {
            attack.b_p2();
        } else {
            attack.b_p3();
        }
    }
}

void Attack::b_p1() {
    botapproachdir = 0;
    approachdir = ball.get_direction() * appraoch_value;
    motor.move(approachdir, approach_speed, 0);
    if (ball.get_distance() < ball_catchdistance) {
        botapproachdir = 
    }
}
