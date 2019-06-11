#include "../states.h"
#include "apogee_state.h"
#include "../utilities/recovery/recovery.h"
#include "../../SD_interface/SD_interface.h"
#include <Arduino.h>
#include "../../sensor_interface/sensor_interface.h"

/*

 Apogee state's main function is to deploy the drogue chute

 */

int apogee_state(double data[]) {
    return_code ret_code;
    
    // Deploys drogue chute instantaneously
    deployDrogueChute(data[TIMESTAMP]);
    getParachute()->drogueDeployed = true;

    write_SD(RECOVERY_FILE, getApogee()->recoveryData, RECOVERY_DATA_LEN);
    
    // Transitions to next state once drogue is deployed
    if (getParachute()->drogueDeployed) {
        get_GPS()->start();
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}