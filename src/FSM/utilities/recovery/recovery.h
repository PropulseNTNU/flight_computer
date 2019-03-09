#pragma once
#ifndef RECOVERY_H
#define RECOVERY_H

#include <Servo.h>
#include "apogee_detect.h"

#define DrogueServoPin 2
#define MainServoPin 3
#define MainChuteALT 457

/*
 Structs and globals not used.
 */

struct ParachuteStateStruct {
    bool drogueDeployed = false; //type uint8_t = 1 byte
    bool mainDeployed = false;
    bool mainStopped = false;
   // ParachuteStateStruct() : drogueDeployed(false), mainDeployed(false), mainStopped(false) {}
};

typedef struct ParachuteStateStruct Parachute;

struct AltitudeStateStruct {
    bool isFalling = false;
    //volatile double currentAltitude;     //data[ALTITUDE]
    volatile double maxAltitude; //type uint64_t = 8 bytes
};

/* Alternative to struct -> array
 enum deployed_parachutes {DROGUE, MAIN_DEPLOY, MAIN_STOP, NUM_TYPES};
 bool parachute_state[NUM_TYPES]; //to access bool variables, then instead of struct pointer we can use array pointer.
 */

ApogeeArray* getApogee();
ParachuteStateStruct* getParachute();

//(Some functions avoided since default initialisation used above)
void setupMainServo(Servo main, int pin);
void setupDrogueServo(Servo drogue, int pin);
void setupParachuteS();
void setupAltitudeS();


//Temporary struct for altitude sim
struct UpdateAltitude {
    bool manual_descend;
    float altitudeUpdate(float h, bool fall)
    {
        if (h < 3000 && !fall) {
            h += 50;
        } else {
            h -= 50;
        }
        return h;
    }
};

void setupCustomAltS(UpdateAltitude* custAlt_pointer);


#endif /* recovery_h */
