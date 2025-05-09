#include <Attack.h>

void Attack::attack() {
   if (line.read() == true) {
       
   } else {
       ball.read();
       if (ball.get_direction() < 10 || ball.get_direction() > 350) {
       }
   }
}
