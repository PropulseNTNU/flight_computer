#ifndef STATES_H
#define STATES_H

//Include states here
#include "states/idle_state.h"
#include "states/armed_state.h"
//#include "liftoff_state.h"
#include "states/burnout_state.h"
#include "states/airbrakes_state.h"
#include "states/apogee_state.h"
#include "states/drogue_state.h"
#include "states/chute_state.h"
#include "states/landed_state.h"

#define ARM_BUTTON_PIN 34
#define RESET_IMU_PIN 23

//All posible states, NUM_STATES is not a state
//Liftoff_state not included
enum state {
	IDLE, ARMED, BURNOUT, AIRBRAKES,
	APOGEE, DROGUE, CHUTE, LANDED, NUM_STATES
};

//The outcomes of running a state-function
enum return_code { NEXT, REPEAT };

typedef int(*state_func)(double[]);
//se på denne, funker ikke c, namespace funker ikke i c
//namespace state {
//	enum type {
//		IDLE/* , ARMED, LIFTOFF, BURNOUT,
//		AIRBRAKES, APOGEE, LANDED*/
//	};
//}

/*
	NB: ACC_X,Y,Z contains linear acceleration + gravity
		GRAVITY_ACCEL_X, Y, Z contains only gravity components
		LINEAR_ACCEL_X,Y,Z contains ONLY linear accelerations.

	Angular velocities in dps per now.
*/
enum datatype {	  TIMESTAMP, BME_TEMP, IMU_TEMP, 
                  PRESSURE, ALTITUDE, 
                  ACC_X, ACC_Y, ACC_Z, 
                  ROLL, PITCH, YAW, 
                  MAG_X, MAG_Y, MAG_Z,
                  ANGULAR_VEL_X,ANGULAR_VEL_Y,ANGULAR_VEL_Z,
                  GRAVITY_ACC_X,GRAVITY_ACC_Y,GRAVITY_ACC_Z, 
                  LINEAR_ACCEL_X,LINEAR_ACCEL_Y,LINEAR_ACCEL_Z,
                  QUATERNION_X, QUATERNION_Y, QUATERNION_Z, QUATERNION_W,
                  STATE, NUM_TYPES
              };
#endif