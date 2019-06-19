#include "../states.h"

double last_data_x = 0;
int increasing_count = 0; // add one to this count each time the rocket acc_x is increasing but negative
int increasing_min_limit = 10; // then rocket needs to have increased its accelleration for increasing_min_limit iterations 
int burntime = 0; // the time the motor has burned
const int burnout_time = 7000; // Milliseconds the rough estimate of how long the motor will burn
const int max_burnout_time = 9000; // Milliseconds the rough estimate of how long the motor will burn
const int epsilon = 1000; // a small time constatnt used for max and min deviation from burnout_time
double launchTime = 0; // the time at launch(motor start)

int burnout_state(double data[]){
	return_code ret_code;

	//get the time at launch so we can estimate burnout time
	if (launchTime == 0) {
		launchTime = data[TIMESTAMP];
	}
	burntime = data[TIMESTAMP] - launchTime;

	if((burntime > (burnout_time + epsilon)) && data[ACC_X] <= 0){
		ret_code = NEXT;
	}
	else if(burntime > max_burnout_time){
		ret_code = NEXT;
	}
	else{
		ret_code = REPEAT;
	}

	return ret_code;
}