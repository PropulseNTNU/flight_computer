using namespace std;
#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include "chute_state.h"
#include <Arduino.h>

/*
 
 This code stops the main servo rotation after a reasonable time -> main released and 200m since fall (~7s)
 
 */

int chute_state(double data[]) {
    return_code ret_code;
    
    if (data[ALTITUDE] <= MainServoEndAlt) {
        
        //Stop or disconnect both motors (necessary with continuous servo)
        getParachute()->mainStopped = true;
    }
    
    if (data[ALTITUDE] <= 5) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}
