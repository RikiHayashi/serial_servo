#include"Servo.h"

int main(int argc, char *argv[]){
	B3MServo b3mservo;

	b3mservo.move(10, 500);
	return 0;
}
