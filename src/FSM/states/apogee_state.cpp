using namespace std;
#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include "apogee_state.h"
#include <Arduino.h>

/*
 
 When arriving at apogee, drogue chute is released immediately -> drogue_state
 
 */

// CHECK Y_Vel or just pitch if it crosses 20 deg also?

static bool drogueDeployed = false;
static PWMServo drogueServo;

int apogee_state(double data[]) {
    return_code ret_code;
    
    if (!drogueDeployed) {
        drogueServo.attach(DrogueServoPin);
        drogueServo.write(5);     //clock-wise
        drogueDeployed = true;
    }
    
    if (drogueDeployed) {
        ret_code = NEXT;
    } else {
        ret_code = REPEAT;
    }
    
    return ret_code;
}

