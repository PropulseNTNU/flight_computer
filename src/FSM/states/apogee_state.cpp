#include "../states.h"
#include "apogee_state.h"
#include "../utilities/recovery/recovery.h"
#include "../../servo_interface/servo_interface.h"
#include "../../SD_interface/SD_interface.h"
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
    
    write_SD(RECOVERY_FILE, getApogee()->apogeeData, 6);
    
    if (getParachute()->drogueDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}

