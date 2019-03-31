#include "recovery.h"
#include "../../../servo_interface/servo_interface.h"
#include "../../../SD_interface/SD_interface.h"


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

AltitudeStruct* getAltitudeStruct() {
    return &apogee;
}

//Ensures deployment of parachutes by stacking write signal. (Necessary? Not sure.)
void deployDrogueChute(double timestamp) {
    for (int i = 0; i < DEPLOY_ATTEMPTS; i++) {
        get_servo(DROGUE_SERVO)->write(DROGUE_DEPLOY_ANGLE);
    }
    getAltitudeStruct()->recoveryData[TIMESTAMP_DROGUE] = timestamp;
}

void deployMainChute(double timestamp) {
    for (int i = 0; i < DEPLOY_ATTEMPTS; i++) {
        get_servo(MAIN_SERVO)->write(MAIN_DEPLOY_ANGLE);
    }
    getAltitudeStruct()->recoveryData[TIMESTAMP_MAIN] = timestamp;
}

//Resets servo positions for testing.
void resetDrogueChute() {
    get_servo(DROGUE_SERVO)->write(DROGUE_RESET_ANGLE);
}

void resetMainChute(){
    get_servo(MAIN_SERVO)->write(MAIN_RESET_ANGLE);
}