#include "../states.h"

void runEntry();
bool entry_ran = false;

int armed_state(double data[]) {
	return_code ret_code;

	if(!entry_ran){
		runEntry();
		entry_ran = true;
	}

	Serial.println("Waiting for y-accel input: must be larger than 15");


	if (data[1] > 15.0) {
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