using namespace std;
#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include <Arduino.h>

int airbrakes_state(double data[]) {
	return_code ret_code;
    
    getApogee()->updateApogeeArray(getApogee(), 0);
    Serial.println("Updated apogee");
    
    Serial.println("Waiting for velocity input: must be less or equal to 1");

	if (1) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}

	return ret_code;
}
