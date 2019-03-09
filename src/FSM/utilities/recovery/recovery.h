#pragma once
#include <PWMServo.h>

#ifndef RECOVERY_H
#define RECOVERY_H

#ifndef DrogueServoPin
#define DrogueServoPin 2
#endif

#ifndef MainServoPin
#define MainServoPin 3
#endif

#ifndef MainChuteALT
#define MainChuteALT 457
#endif

/*
 Structs and globals not used.
 */

struct ParachuteStateStruct {
    bool drogueDeployed; //type uint8_t = 1 byte
    bool mainDeployed;
    bool mainStopped;
} ;


struct AltitudeStateStruct {
    bool isFalling;
    //volatile double currentAltitude;     //data[ALTITUDE]
    volatile double maxAltitude; //type uint32_t = 4 bytes
};

/* Alternative to struct -> array
 enum deployed_parachutes {DROGUE, MAIN_DEPLOY, MAIN_STOP, NUM_TYPES};
 bool parachute_state[NUM_TYPES]; //to access bool variables, then instead of struct pointer we can use array pointer.
 */


//Setup done in armed_state.cpp (Some functions avoided since default initialisation used above)
void setupMainServo(PWMServo main, int pin);
void setupDrogueServo(PWMServo drogue, int pin);
void setupParachuteS(ParachuteStateStruct* parachute_pointer);
void setupAltitudeS(AltitudeStateStruct* alt_pointer);


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
