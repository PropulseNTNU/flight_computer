#include "../states.h"
#include "../../sensor_interface/sensor_interface.h"
#include "../../servo_interface/servo_interface.h"

//Only the arm button should trigger next state
int idle_state(double data[]) {
	return_code ret_code;

	get_servo(AIRBRAKES_SERVO)->write(0);

	if (digitalRead(ARM_BUTTON_PIN)){
		get_GPS()->stop();
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}