#include "../states.h"
#include "apogee_state.h"
#include "../utilities/recovery/recovery.h"
#include "../../SD_interface/SD_interface.h"
#include <Arduino.h>

/*
 
 When arriving at apogee, drogue chute is released immediately -> drogue_state
 
 */

int apogee_state(double data[]) {
    return_code ret_code;
    
    if (!getParachute()->drogueDeployed) {
        deployDrogueChute(data[TIMESTAMP]);
        getParachute()->drogueDeployed = true;
    }
    
    write_SD(RECOVERY_FILE, getApogee()->recoveryData, RECOVERY_DATA_LEN);
    
    if (getParachute()->drogueDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}

