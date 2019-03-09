#include "recovery.h"

/*
 initialise globals to be used in setup & loop
 */

ParachuteStateStruct parachute;
AltitudeStateStruct alt;
ApogeeArray apogee;


//get functions
ParachuteStateStruct* getParachute() {
    return &parachute;
}

ApogeeArray* getApogee() {
    return &apogee;
}

AltitudeStateStruct* getAlt() {
    return &alt;
}

//initialise parachute states
void setupParachuteS() {  //takes in p_parachute in armed state
    getParachute()->drogueDeployed = false;
    getParachute()->mainDeployed = false;
    getParachute()->mainStopped = false;
}

//initialise altitude state
void setupAltitudeS() { //takes in p_altitude in armed state, data_alt is altitude in data array.
    getAlt()->isFalling = false;   //skal peke noen andre steder
    //alt_pointer->currentAltitude = data_altitude;
    getAlt()->maxAltitude = -1;
}

//initialise altitude simulator
void setupCustomAltS(UpdateAltitude* custAlt_pointer) { //takes in p_customAltitude in armed state
    custAlt_pointer->manual_descend = false;
}
