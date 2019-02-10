using namespace std;
#include "../states.h"
#include <Arduino.h>

//Next state Aibrakes should be triggered once a_z = 0.
int burnout_state(double data[]) {
	return_code ret_code;
	Serial.println("Waiting for z-accel input: must be less or equal to 0");
	if (data[ACC_Z] <= 10.0) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}

	return ret_code;
}