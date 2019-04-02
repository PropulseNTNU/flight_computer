#ifndef RECOVERY_H
#define RECOVERY_H

#include <Servo.h>
#include "apogee_detect.h"

#define MainChuteALT 457
#define DEPLOY_ATTEMPTS 5

typedef struct ParachuteStateStruct {
    bool drogueDeployed = false;
    bool mainDeployed = false;
} Parachute;

// Get functions to return pointers to objects
ParachuteStateStruct* getParachute();
ApogeeArray* getApogee();
AltitudeStruct* getAltitudeStruct(); //Alias for getApogee()

// Deploys parachutes in apogee_state and drogue_state
void deployDrogueChute(double timestamp);
void deployMainChute(double timestamp);

#endif /* recovery_h */
