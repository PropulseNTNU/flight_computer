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
/*
#include "landed_state.h"*/

//All posible states, NUM_STATES is not a state
enum state {
	IDLE, ARMED, LIFTOFF, BURNOUT, AIRBRAKES,
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

enum datatype {TIMESTAMP, BME_TEMP, IMU_TEMP, 
                  PRESSURE, ALTITUDE, 
                  ACC_X, ACC_Y, ACC_Z, 
                  PITCH, ROLL, YAW, 
                  MAG_X, MAG_Y, MAG_Z, NUM_TYPES};
#endif