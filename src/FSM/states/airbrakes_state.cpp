#include "../states.h"
#include "../utilities/recovery/recovery.h"
#include "../utilities/airbrakes/controll.h"
#include "../utilities/airbrakes/interpolation.h"
#include "../utilities/airbrakes/kalman.h"
#include "../../servo_interface/servo_interface.h"
#include "../../SD_interface/SD_interface.h"
#include <Arduino.h>

//initilises variables
float error = 0; //error used in controller
float riemann_sum = 0; //used in integrator, witch is used in controller
float u = 0;
float dt = 0; //time step used in integrator and kalman filter
ControlParameters parameters = { 1 , 0.01 , 1 }; //Control parameters (Kp, Ki, Kd)
unsigned long time_old = 0; // time variable for delta time

float sensor_data[2]={0,0}; //Barometer at index 0 and accelrometer (z-direction)at index 1. Utvides kanskje senere m/pitch
float estimates[2] = {0,0}; //Estimates from Kalman filter. [height, velocity]
float reference_v = 0; //reference_velovity
bool firstIter = true; // a boolean value so we know if we are in the first iteration. Used for handeling dt the first iteration.
const int default_rotation = 30;

int airbrakes_state(double data[]) {
	return_code ret_code;
    
	dt = (float)(data[TIMESTAMP] - time_old);
	dt /= (float)1000; // converted to seconds
	time_old = data[TIMESTAMP];

	if(firstIter){
		dt = 0.00014;
		firstIter = false;
	}
	else{
		//estimate the velocity and altitude using a kalman filter with accelleration and altitude as input
		kalman(estimates, data[ALTITUDE], data[ACC_X], dt, reference_v);
	}

	// calculate the reference velocity we should have at the given altitude.
	reference_v = getReferenceVelocity(estimates[0]);
	// get the error which is how far the rockets velocity is from the optimal velocity
	error = estimates[1] - reference_v;
	// calculate the servo control signal using the error
	u = default_rotation + controller(&error, &parameters, &riemann_sum, dt); //updates controll signal

	// write error and controll signal too file before if statement
	if(u > 60) {
		get_servo(AIRBRAKES_SERVO)->write(60); //updates servo position
	}
	else if(u < 0){
		get_servo(AIRBRAKES_SERVO)->write(0); //updates servo position
	}
	else{
		get_servo(AIRBRAKES_SERVO)->write(u); //updates servo position
	}

    // This updates the ApogeeArray with current altitude
    getAltitudeStruct()->updateDataArray(getAltitudeStruct(), (double)estimates[0]); //kalman_altitude == estimates[0]
	
	// write values from both airbrakes and recovery to SD card
	if ((millis() - *getLastLog(COMMON_LASTLOG)) >= *getLogInterval(AIRBRAKES_INTERVAL)) {
		setLastLog(millis(), COMMON_LASTLOG);
		// these values may be nan during testing since the lookup table or sensors may be missing
		double abValues[4] = {data[TIMESTAMP], estimates[0], estimates[1], u};
		write_SD(AIRBRAKES_FILE, abValues, 4);
        // writing recovery values
		write_SD(RECOVERY_FILE, getApogee()->recoveryData, RECOVERY_DATA_LEN);
	}
	
    // Directly checks if average altitude falls below max altitude by a margin
	if (apogeeDetected(getApogee(), data) && estimates[0] > 2000) {
		get_servo(AIRBRAKES_SERVO)->write(0); 
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}

	return ret_code;
}
