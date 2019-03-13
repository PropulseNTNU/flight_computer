#ifndef STATES_H
#define STATES_H

#include "states/idle_state.h"
#include "states/armed_state.h"
//#include "liftoff_state.h"
#include "states/burnout_state.h"
#include "states/airbrakes_state.h"
#include "states/apogee_state.h"
#include "states/drogue_state.h"
#include "states/chute_state.h"
#include "states/landed_state.h"
#include "../sensor_interface/sensor_data.h"
#include <Arduino.h>

//All posible states, NUM_STATES is not a state
//Liftoff_state not included
enum state {
	IDLE, ARMED, BURNOUT, AIRBRAKES,
	APOGEE, DROGUE, CHUTE, LANDED, NUM_STATES
};

//The outcomes of running a state-function
enum return_code { NEXT, REPEAT };

typedef int(*state_func)(double[]);


#endif