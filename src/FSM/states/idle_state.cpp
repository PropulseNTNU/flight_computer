using namespace std;
#include "../states.h"
#include <Arduino.h>

//Only the arm button b should trigger next state
int idle_state(double data[]) {
	return_code ret_code;

	
	if (true){
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}
	return ret_code;
}