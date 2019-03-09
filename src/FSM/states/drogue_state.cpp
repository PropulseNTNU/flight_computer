using namespace std;
#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include "../../servo_interface/servo_interface.h"
#include "drogue_state.h"
#include <Arduino.h>

/*
 
 State assumes drogue released. Continually checks criteria to release main.
 
 */

int drogue_state(double data[]) {
    return_code ret_code;
    
    if ((!getParachute()->mainDeployed) && (data[ALTITUDE] <= MainChuteALT)) {
        get_servo(MAIN_SERVO)->write(5);
        getParachute()->mainDeployed = true;
    }
    
    if (getParachute()->mainDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}
