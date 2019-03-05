#include "recovery.h"

// Code version 2.0 - organised globals into struct
// by Eivind and Patrick

//Propulse NTNU

/*
 initialise globals to be used in setup & loop
 */
extern PWMServo drogueServo;
extern PWMServo mainServo;

extern ParachuteStateStruct parachute_default;
extern AltitudeStateStruct alt_default;
extern ParachuteStateStruct* p_parachute;
extern AltitudeStateStruct* p_altitude;


//initialise Servo and start position (pos. maybe unnecessary for final thing)

void setupMainServo(PWMServo main, int pin) {
    main.attach(pin);
    main.write(85);     //Writes 85 deg. Should then be neutral. (Not rotating)
}

void setupDrogueServo(PWMServo drogue, int pin) {
    drogue.attach(pin);
    drogue.write(85);   //Writes 85 deg. Not so important.
}


//initialise parachute states
void setupParachuteS(ParachuteStateStruct* parachute_pointer) {  //takes in p_parachute in armed state
    parachute_pointer->drogueDeployed = false;
    parachute_pointer->mainDeployed = false;
    parachute_pointer->mainStopped = false;
}


//initialise altitude state
void setupAltitudeS(AltitudeStateStruct* alt_pointer) { //takes in p_altitude in armed state, data_alt is altitude in data array.
    alt_pointer->isFalling = false;   //skal peke noen andre steder
    //alt_pointer->currentAltitude = data_altitude;
    alt_pointer->maxAltitude = -1;
}


//initialise altitude simulator
void setupCustomAltS(UpdateAltitude* custAlt_pointer) { //takes in p_customAltitude in armed state
    custAlt_pointer->manual_descend = false;
}
