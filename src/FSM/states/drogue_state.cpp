#include "../states.h"
#include "drogue_state.h"
#include "../utilities/recovery/recovery.h"
#include "../../SD_interface/SD_interface.h"
#include <Arduino.h>

/*
 
 Drogue state's function is to deploy the main chute when the altitude drops below 457m
 
 */

int drogue_state(double data[]) {
    return_code ret_code;
    
    // This updates the altitude array with current altitude, done here to access altitude table
    getAltitudeStruct()->updateDataArray(getAltitudeStruct(), data[1]);
    
    // Criteria directly based on average altitude (last 10 measurements) being less than 457m
    if ((!getParachute()->mainDeployed) && (getAltitudeStruct()->recoveryData[AVERAGE_ALTITUDE] <= MainChuteALT)) {
        deployMainChute(data[TIMESTAMP]);
        getParachute()->mainDeployed = true;
    }
    
    // Write to SD card
    if ((millis() - *getLastLog(COMMON_LASTLOG) >= *getLogInterval(DROGUE_INTERVAL))) {
        setLastLog(millis(), COMMON_LASTLOG);
        write_SD(RECOVERY_FILE, getAltitudeStruct()->recoveryData, RECOVERY_DATA_LEN);
    }
    
    // Transitions to next state once main chute is deployed
    if (getParachute()->mainDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}
