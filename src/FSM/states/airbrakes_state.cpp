using namespace std;
#include "../states.h"
#include <Arduino.h>

int airbrakes_state(double data[]) {
	return_code ret_code;

	Serial.println("Waiting for velocity input: must be less or equal to 1");

	if (data[ACC_Z] <= 1) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}

	return ret_code;
}
