using namespace std;
#include "../states.h"

double last_acc_z = 0;
int increasing_count = 0; // add one to this count each time the rocket acc_z is increasing but negative
int increasing_min_limit = 10; // then rocket needs to have increased its accelleration for increasing_min_limit iterations 
int burntime = 0; // the time the motor has burned
const int burnout_time = 6000; // Milliseconds the rough estimate of how long the motor will burn
const int epsilon = 200; // a small time constatnt used for max and min deviation from burnout_time
double launchTime = 0; // the time at launch(motor start)

int burnout_state(double data[]) {
	return_code ret_code;

	//get the time at launch so we can estimate burnout time
	if(launchTime == 0){
		launchTime = data[TIMESTAMP];
	}
	burntime = data[TIMESTAMP] - launchTime;

	//if acc_z is negative but increasing
	if(data[ACC_Z] > last_acc_z && last_acc_z < 0){
		// increment the increasing count
		increasing_count += 1;
	}
	last_acc_z = data[ACC_Z];

	// if data[ACC_Z] is negative but increasing, and time is more than burntime - epsilon
	// or time is more than burntime + epsilon which is the uppper limit.
	if ((increasing_count > increasing_min_limit && burnout_time > (burnout_time - epsilon)) || (burntime > burnout_time + epsilon)) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}

	return ret_code;
}