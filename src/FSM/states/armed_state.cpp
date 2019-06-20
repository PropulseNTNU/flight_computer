#include "../states.h"


int armed_state(double data[]) {
	return_code ret_code;

	Serial.println("Waiting for x-accel input: must be larger than 15");

	if (data[LINEAR_ACCEL_X] > 15.0) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}