#include "../states.h"
<<<<<<< HEAD
#include "../utilities/recovery/recovery.h"
#include "../../servo_interface/servo_interface.h"
#include "drogue_state.h"
#include <Arduino.h>
=======
>>>>>>> 37a58a340beb604752c2d6923f38549074f0c750

/*
 
 State assumes drogue released. Continually checks criteria to release main.
 
 */

int drogue_state(double data[]) {
    return_code ret_code;
    
    //This updates the altitude array with current altitude, done here to access altitude table.
    getApogee()->updateApogeeArray(getApogee(), data[ALTITUDE]);
    
    //Criteria directly based on average altitude (last 10 measurements) being less than 457m.
    if ((!getParachute()->mainDeployed) && (getApogee()->apogeeData[AVERAGE_ALTITUDE] <= MainChuteALT)) {
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
