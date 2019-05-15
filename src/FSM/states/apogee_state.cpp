#include "../states.h"
#include "apogee_state.h"
#include "../utilities/recovery/recovery.h"
#include "../../SD_interface/SD_interface.h"
#include <Arduino.h>

/*

 Apogee state's main function is to deploy the drogue chute

 */

int apogee_state(double data[]) {
    return_code ret_code;
    
    // Deploys drogue chute instantaneously
    deployDrogueChute(data[0]);
    getParachute()->drogueDeployed = true;

    write_SD(RECOVERY_FILE, getApogee()->recoveryData, RECOVERY_DATA_LEN);
    
    // Transitions to next state once drogue is deployed
    if (getParachute()->drogueDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}