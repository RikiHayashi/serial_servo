#ifndef _SERVO_
#define _SERVO_

#include "vector"
#include"Futaba.h"

using namespace std;


class FutabaLeg {
	public:
		FutabaLeg() : futaba("/dev/ttyUSB0"){
			offset_load((char *)"offset.txt");
			for(int id=1; id<12; id++){
				futaba.set_mode(id, Futaba::MODE::Free);
			}
			cout << "set Free" << endl;
			futaba.servo_sleep(1);
			for(int id=1; id<12; id++){
				futaba.set_mode(id, Futaba::MODE::Normal);
			}
			cout << "set Normal" << endl;
			futaba.servo_sleep(1);
			init_leg();
		}

		void init_leg();
		void ready_leg(vector<int> angle);
		void move_leg(vector<int> angle, double time);
		int offset_load(char *filename);

		Futaba::Futaba futaba;
	public:
		std::array<double, 30> offset;
		std::vector<double> ID{6,5,4,3,2,1,12,11,10,9,8,7};
		std::vector<double> var{1,1,-1,-1,1,1,1,1,1,1,-1,1};
};

#endif

