#include "recovery_main.hpp"
// Code version 2.0 - organised globals into struct
// by Eivind and Patrick

//Propulse NTNU

#include <PWMServo.h>

PWMServo drogueServo;
PWMServo mainServo;

/*
 initialise globals to be used in setup & loop
*/

/*
//VERSION 1
ParachuteStateStruct* p_parachute = (ParachuteStateStruct*) malloc(sizeof(ParachuteStateStruct));
AltitudeStateStruct* p_altitude = (AltitudeStateStruct*) malloc(sizeof(AltitudeStateStruct));
UpdateAltitude* p_customAltitude = (UpdateAltitude*) malloc(sizeof(UpdateAltitude));
*/

//VERSION 2
ParachuteStateStruct* p_parachute = &parachute;  //Define parachute after struct
AltitudeStateStruct* p_altitude = &alt;
UpdateAltitude* p_customAltitude = &customAlt;

//initialise Servo and start position
mainServo.attach(MainServoPin);
mainServo.write(85);
drogueServo.attach(DrogueServoPin);
drogueServo.write(85);

//initialise parachute states
p_parachute->drogueDeployed = false;
p_parachute->mainDeployed = false;
p_parachute->mainStopped = false;

//initialise altitude state
p_altitude->isFalling = false;   //skal peke noen andre steder
p_altitude->currentAltitude = 0;
p_altitude->maxAltitude = -1;

//initialise altitude simulator
p_customAltitude->manual_descend = false;


