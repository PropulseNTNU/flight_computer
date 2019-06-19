#include "../states.h"
#include "../../sensor_interface/sensor_interface.h"

int armed_state(double data[]) {
	return_code ret_code;

	Serial.println("Waiting for x-accel input: must be larger than 15");

	if (data[LINEAR_ACCEL_X] > 15.0) {
		get_GPS()->stop();
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}