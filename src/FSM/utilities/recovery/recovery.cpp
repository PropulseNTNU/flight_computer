#include "recovery.h"

/*
 Declare globals
 */

Parachute parachute;
ApogeeArray apogee;


//Get functions
Parachute* getParachute() {
    return &parachute;
}

ApogeeArray* getApogee() {
    return &apogee;
}
