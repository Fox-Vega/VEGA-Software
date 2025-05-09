#include <Attack.h>

void Attack::attack() {
    if (line.read() == true) {
       
    } else {
        ball.read();
        ball_dir = ball.get_direction();
        if (ball_dir < 10 || ball_dir > 350) {
            attack.b_p1();
        } else if (ball.get_distance > BallApproach_radius) {
            attack.b_p2();
        } else {
            attack.b_p3();
        }
    }
}
