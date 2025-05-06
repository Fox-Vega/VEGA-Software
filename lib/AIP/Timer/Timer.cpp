#include "timer.h"


void timer::reset(){
	milliseconds = millis();
	microseconds = micros();
}

unsigned long timer::read_milli(){
	return (millis() - milliseconds);
}

unsigned long timer::read_micro(){
	return (micros() - microseconds);
}