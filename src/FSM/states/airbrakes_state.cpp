using namespace std;
#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include <Arduino.h>
#include "../utilities/airbrakes/controll.h"
#include "../utilities/airbrakes/interpolation.h"
#include "../utilities/airbrakes/kalman.h"
#include "airbrakes_state.h"
#include "../../servo_interface/servo_interface.h"

//initilises variables
float error = 0; //error used in controller
float riemann_sum = 0; //used in integrator, witch is used in controller
float u = 90; //sets servo to 90 degrees, this causes the air brakes to brake at 50% capasaty
float dt = 0; //time step used in integrator and kalman filter
Parameters parameters = { 1 , 1 , 1 }; //Control parameters (Kp, Ki, Kd)
unsigned long time_old = 0; // time variable for delta time

float sensor_data[2]={0,0}; //Barometer at index 0 and accelrometer (z-direction)at index 1. Utvides kanskje senere m/pitch
float estimates[2]; //Estimates from Kalman filter. [height, velocity]
float reference_v= 200; //reference_velovity
bool firstIteration = true;

int airbrakes_state(double data[]) {
	return_code ret_code;
    
	//Updats dt
	dt = (float)(data[TIMESTAMP] - time_old);
	dt /= (float)1000; // converted to seconds
	time_old = data[TIMESTAMP];

	kalman(estimates, data[ALTITUDE], data[ACC_Z], dt, reference_v);
	// write kalman values to file
	reference_v = getReferenceVelocity(estimates[0]);
	error = reference_v - estimates[1];
	u += controller(&error, &parameters, &riemann_sum, dt); //updates controll signal

	// write error and controll signal too file before if statement
	if(u >= 0 && u <= 180) {
		get_servo(AIRBRAKES_SERVO)->write(u); //updates servo position
	}
    
    
    getApogee()->updateApogeeArray(getApogee(), data[ALTITUDE]); //This updates the ApogeeArray with current altitude

    // remmember to update this to correct tests
	if (apogeeDetected(getApogee(), data)) {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}

	return ret_code;
}
