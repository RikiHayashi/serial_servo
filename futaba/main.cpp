#include"Servo.h"

int main(int argc, char *argv[]){
	FutabaLeg futabaleg;
	vector<double> ready(12, 0);
	vector<double> angle(12, 0);

	ready[1] = 10.0;

	futabaleg.ready(ready);

	futabaleg.move(angle, 10);
	return 0;
}
