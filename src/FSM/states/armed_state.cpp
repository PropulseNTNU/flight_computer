using namespace std;
#include "../states.h"
#include <Arduino.h>

void runEntry();
bool entry_ran = false;

/*
	Event detection:
		Model rocket start accel: 86m/s^2

		Sleipner:

	NB: IMU detects only 16g????
*/

int armed_state(double data[]) {
	return_code ret_code;

	if(!entry_ran){
		runEntry();
		entry_ran = true;
	}

	Serial.println("Waiting for z-accel input: must be larger than 12");


	if (data[ACC_Z] > 15.0) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}

/*	
	The entry() function is run once after transitioning to this state.
	Place initialization procedures inside the entry function.
*/
void runEntry(){
}