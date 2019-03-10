using namespace std;
#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include "../../servo_interface/servo_interface.h"
#include "apogee_state.h"
#include <Arduino.h>

/*
 
 When arriving at apogee, drogue chute is released immediately -> drogue_state
 
 */

int apogee_state(double data[]) {
    return_code ret_code;
    
    if (!getParachute()->drogueDeployed) {
        get_servo(DROGUE_SERVO)->write(5);
        getParachute()->drogueDeployed = true;
    }
    
    if (getParachute()->drogueDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}

