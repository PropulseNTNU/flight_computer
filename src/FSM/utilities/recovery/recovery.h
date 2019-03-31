#pragma once
#ifndef RECOVERY_H
#define RECOVERY_H

#include <Servo.h>
#include "apogee_detect.h"

#define DrogueServoPin 2
#define MainServoPin 3
#define MainChuteALT 457
#define DROGUE_DEPLOY_ANGLE 30 //Tested
#define DROGUE_RESET_ANGLE 145 //Tested
#define MAIN_DEPLOY_ANGLE 5 //To be tested
#define MAIN_RESET_ANGLE 165 //To be tested
#define DEPLOY_ATTEMPTS 5


struct ParachuteStateStruct {
    bool drogueDeployed = false; //type uint8_t = 1 byte
    bool mainDeployed = false;
   // (Constructor Option) ParachuteStateStruct() : drogueDeployed(false), mainDeployed(false) {}
};

typedef struct ParachuteStateStruct Parachute;

/* Alternative to struct -> array
 enum deployed_parachutes {DROGUE, MAIN_DEPLOY, NUM_TYPES};
 bool parachute_state[NUM_TYPES]; //to access bool variables, then instead of struct pointer we can use array pointer.
 */

ParachuteStateStruct* getParachute();
ApogeeArray* getApogee();
AltitudeStruct* getAltitudeStruct(); //Alias for getApogee()

//Deploys parachutes in apogee_state and drogue_state.
void deployDrogueChute(double timestamp);
void deployMainChute(double timestamp);

//Resets servo position for testing.
void resetDrogueChute();
void resetMainChute();

#endif /* recovery_h */
