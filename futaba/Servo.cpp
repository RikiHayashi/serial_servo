#include"Servo.h"

void FutabaLeg::init(){
	for(int id=1; id<12; id++){
		futaba.set_angle(id, 0.0+offset[id-1], 300);
		futaba.servo_usleep(100);
	}
	futaba.servo_sleep(3000);
}

void FutabaLeg::ready(vector<double> angle){
	for(int id=1; id<12; id++){
		futaba.set_angle(id, angle[ID[id]]*var[ID[id]]*0.01+offset[id-1], 300);
		futaba.servo_usleep(100);
	}
	futaba.servo_sleep(3000);
}

/* angle:deg, time:ms*/
void FutabaLeg::move(vector<double> angle, double time){
	for(int id=1; id<12; id++){

		futaba.set_angle(id,angle[ID[id]]*var[ID[id]]*0.01+offset[id-1], time);
		futaba.servo_usleep(100);
	}
	futaba.servo_sleep(time);
}

int FutabaLeg::offset_load(char *filename){
	char off_tmp[30];
	int id, angle;
	FILE *fp;

	if(NULL == (fp = fopen(filename,"r"))){
		std::cerr << "cannot open file" << filename << std::endl;
		return -1;
	}
	while(fscanf(fp, "%d %d", &id, &angle) != EOF){
		offset[id] = angle * 0.01;
	}
	fclose(fp);

	return 0;
}

