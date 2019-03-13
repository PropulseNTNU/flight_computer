#include "../states.h"
#include "chute_state.h"
#include "../utilities/recovery/recovery.h"
#include "../../SD_interface/SD_interface.h"
#include <Arduino.h>

/*
 
 This code stops the main servo rotation after a reasonable time -> main released and 200m since fall (~7s).
 If non-continuous servo, code is redundant.
 
 */

int chute_state(double data[]) {
    return_code ret_code;
    
    //This updates the altitude array with current altitude, done here to access altitude table.
    getAltitudeStruct()->updateDataArray(getApogee(), data);
    
    if (getAltitudeStruct()->recoveryData[AVERAGE_ALTITUDE]  <= MainServoEndAlt) {
        
        //Stop or disconnect both motors here (necessary with continuous servo)
        
        getParachute()->mainStopped = true;
    }
    
    //Write to SD card
    if ((millis() - *getLastLog(COMMON_LASTLOG) >= *getLogInterval(CHUTE_INTERVAL))) {
        setLastLog(millis(), COMMON_LASTLOG);
        // writing recovery values
        write_SD(RECOVERY_FILE, getAltitudeStruct()->recoveryData, RECOVERY_DATA_LEN);
    }
    
    if (data[ALTITUDE] <= 5) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}
