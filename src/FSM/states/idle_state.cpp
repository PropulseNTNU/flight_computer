using namespace std;
#include "../states.h"
#include <Arduino.h>

//Only the arm button b should trigger next state
int idle_state(double data[]) {
	return_code ret_code;
	String arm;
	Serial.println("Arm rocket by pushing b" );
	arm = Serial.read();
	//Serial.println(data[1]);
	delay(400);
	if (arm == "b") {
		Serial.println("rocket armed!" );
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}