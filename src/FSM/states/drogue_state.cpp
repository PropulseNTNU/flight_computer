using namespace std;
#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include "drogue_state.h"
#include <Arduino.h>

/*
 
 State assumes drogue released. Continually checks criteria to release main.
 
 */

static bool doSetup = true;
static bool mainDeployed = false;
static PWMServo mainServo;


int drogue_state(double data[]) {
    return_code ret_code;
    
    if (doSetup) {
        mainServo.attach(MainServoPin);
        doSetup = false;
    }
    
    if ((!mainDeployed) && (data[ALTITUDE] <= MainChuteALT)) {
        mainServo.write(0);     //clock-wise
        mainDeployed = true;
    }
    
    if (mainDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}
