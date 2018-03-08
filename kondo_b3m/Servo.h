#ifndef _SERVO_
#define _SERVO_

#include"vector"
#include"B3M.h"

using namespace std;

class B3MServo {
	public:
		int id;
		B3MServo() : b3m("/dev/ttyUSB0"), id(0){
			b3m.set_mode(id, B3M::MODE::Free);
			cout << "set Free" << endl;
			b3m.servo_sleep(1);
			b3m.set_mode(id, B3M::MODE::Normal);
			cout << "set Normal" << endl;
			b3m.servo_sleep(1);
			init();
		}

		void init();
		void move(double angle, double time);

		B3M::B3M b3m;
};

#endif
