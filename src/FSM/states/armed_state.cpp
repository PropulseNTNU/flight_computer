using namespace std;
#include "../states.h"
#include <Arduino.h>

int armed_state(double data[]) {
	return_code ret_code;
	Serial.println("Waiting for z-accel input: must be larger than 12");
	
	if (data[ACC_Z] > 12.0) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}