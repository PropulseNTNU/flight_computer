#ifndef recovery_main_hpp
#define recovery_main_hpp

struct ParachuteStateStruct {
    bool drogueDeployed; //type uint8_t = 1 byte
    bool mainDeployed;
    bool mainStopped;
} parachute;


struct AltitudeStateStruct {
    bool isFalling;
    volatile float currentAltitude;
    volatile float maxAltitude; //type uint32_t = 4 bytes
} alt;


/* Alternatively
 
 enum deployed_parachutes {DROGUE, MAIN_DEPLOY, MAIN_STOP, NUM_TYPES};
 bool parachute_state[NUM_TYPES]; //to access bool variables, then instead of struct pointer we can use array pointer.
 
 */


//Temporary struct to simulate altitude
struct UpdateAltitude {
    bool manual_descend;
    float altitudeUpdate(float h, bool fall)
    {
        if (h < 3000 && !descend) {
            h += 50;
        } else {
            h -= 50;
        }
        return h;
    }
} customAlt;


#endif /* recovery_main_hpp */
