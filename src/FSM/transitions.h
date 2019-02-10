#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "states.h"

//Transition struct
struct transition {
	enum state source_state;
	enum return_code ret_code;
	enum state destination_state;
};

state lookup_transition(state current_state, return_code rc);

#endif