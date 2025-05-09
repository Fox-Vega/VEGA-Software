#include <Attack.h>

void Attack::attack() {
    if (line.read() == true) {
       
    } else {
        ball.read();
        if (ball.get_direction() < 10 || ball.get_direction() > 350) {
            attack.b_p1();
        } else if (ball.get_distance > wrap_rad) {
            attack.b_p2();
        } else {
            attack.b_p3();
        }
    }
}
