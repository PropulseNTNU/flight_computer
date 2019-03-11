#include "../states.h"

//Only the arm button should trigger next state
int idle_state(double data[]) {
	return_code ret_code;

	if (digitalRead(ARM_BUTTON_PIN)){
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}