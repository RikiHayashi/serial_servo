#include"Servo.h"

void B3MServo::init(){
	b3m.set_angle(id, 0, 1);
	b3m.servo_usleep(250);
}

void B3MServo::move(double angle, double time){
	b3m.set_angle(id, angle, time);
	b3m.servo_usleep(250);
}
