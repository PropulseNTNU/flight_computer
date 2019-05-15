#include "../states.h"
#include "chute_state.h"
#include "../utilities/recovery/recovery.h"
#include "../../SD_interface/SD_interface.h"
#include <Arduino.h>

/*
 
 State transitions once altitude is below 5m
 
*/

int chute_state(double data[]) {
    return_code ret_code;
    
    // This updates the altitude array with current altitude, done here to access altitude table
    getAltitudeStruct()->updateDataArray(getAltitudeStruct(), data[1]);
    
    // Write to SD card
    if ((millis() - *getLastLog(COMMON_LASTLOG) >= *getLogInterval(CHUTE_INTERVAL))) {
        setLastLog(millis(), COMMON_LASTLOG);
        write_SD(RECOVERY_FILE, getAltitudeStruct()->recoveryData, RECOVERY_DATA_LEN);
    }
    
    if (data[1] <= 5) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}
