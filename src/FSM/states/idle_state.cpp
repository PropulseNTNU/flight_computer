#include "../states.h"
#include "../../sensor_interface/sensor_interface.h"


//Only the arm button should trigger next state
int idle_state(double data[]) {
	return_code ret_code;

	if (digitalRead(ARM_BUTTON_PIN)){
		GPS::getInstance().start();
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}