using namespace std;
#include "../states.h"
#include "../utilities/recovery.h"
#include "apogee_state.h"
#include <Arduino.h>
#include <PWMServo.h>

//Initialise variables
bool doSetup = true;

int apogee_state(double data[]) {
	return_code ret_code;
	
	if (doSetup == true) {
		drogueServo.attach(DrogueServoPin);
	}

	drogueServo.write(5);     //clock-wise
	p_parachute->drogueDeployed = true;
	
	if (p_parachute->drogueDeployed == true) {
		ret_code = REPEAT;
	} else {
		ret_code = DROGUE_STATE;
	}
	
	
	return ret_code;
}


