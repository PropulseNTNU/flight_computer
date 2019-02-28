#include "recovery_main.hpp"
// Code version 2.0 - organised globals into struct
// by Eivind and Patrick

//Propulse NTNU

#include <PWMServo.h>

#define MainChuteALT 457
#define DrogueServoPin 2
#define MainServoPin 3

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
 



void setup() {
    Serial.begin(9600);
    
    
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
}


void loop() {
    while (!p_parachute->mainStopped) {
        
        //Read altitude here
        p_altitude->currentAltitude = p_customAltitude->altitudeUpdate(p_altitude->currentAltitude, p_customAltitude->manual_descend);
        
        
        //Update variables
        if (p_altitude->currentAltitude > p_altitude->maxAltitude) {
            p_altitude->maxAltitude = p_altitude->currentAltitude;
        }
        Serial.print("Altitude: ");
        Serial.println(p_altitude->currentAltitude);
        
        
        //Update orientation
        if (p_altitude->currentAltitude >= 3000) {
            p_customAltitude->manual_descend = true;
            Serial.println("Descending!");
        }
        
        
        //Check conditions
        if ((!p_altitude->isFalling) && (p_altitude->currentAltitude <= (p_altitude->maxAltitude-20))) {
            p_altitude->isFalling = true;
            Serial.println("Falling!");
        }
        
        if ((!p_parachute->drogueDeployed) && (p_altitude->isFalling) && (p_altitude->currentAltitude <= (p_altitude->maxAltitude-25))) {
            drogueServo.write(5);     //clock-wise
            p_parachute->drogueDeployed = true;
            Serial.println("Drogue!");
        }
        
        if ((!p_parachute->mainDeployed) && (p_parachute->drogueDeployed) && (p_altitude->currentAltitude <= MainChuteALT)) {
            mainServo.write(0);     //clock-wise
            p_parachute->mainDeployed = true;
            Serial.println("Main!");
        }
        
        if ((p_parachute->mainDeployed) && (p_altitude->currentAltitude <= (MainChuteALT-200))) {
            mainServo.write(85);    //Stop
            p_parachute->mainStopped = true;
            Serial.println("Main stop!");
        }
        
        delay(100);
    }
    /*
    free(p_parachute);
    free(p_altitude);
    free(p_customAltitude);
    */
}

