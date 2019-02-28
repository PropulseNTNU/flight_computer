using namespace std;
#include "../states.h"
#include "../utilities/recovery.h"
#include "apogee_state.h"
#include <Arduino.h>
#include <PWMServo.h>

int apogee_state(double data[]) {
	return_code ret_code;
	ret_code = REPEAT;
	return ret_code;
}

PWMServo drogueServo;

drogueServo.attach(DrogueServoPin);

drogueServo.write(5);     //clock-wise
p_parachute->drogueDeployed = true;
