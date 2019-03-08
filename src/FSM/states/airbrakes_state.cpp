using namespace std;
#include "../states.h"
#include "../utilities/airbrakes/controll.h"
#include "../utilities/airbrakes/interpolation.h"
#include "../utilities/airbrakes/kalman.h"
#include "airbrakes_state.h"
#include <Servo.h>

//initilises variables
float error = 0; //error used in controller
float riemann_sum = 0; //used in integrator, witch is used in controller
float u = 90; //sets servo to 90 degrees, this causes the air brakes to brake at 50% capasaty
float dt = 0; //time step used in integrator and kalman filter
Parameters parameters = { 1 , 1 , 1 }; //Control parameters (Kp, Ki, Kd)
unsigned long time_new, time_old = 0; // time variables for delta time

float sensor_data[2]={0,0}; //Barometer at index 0 and accelrometer (z-direction)at index 1. Utvides kanskje senere m/pitch
float estimates[2]; //Estimates from Kalman filter. [height, velocity]
float reference_v= 200; //reference_velovity
bool firstIteration = true;

//Airbrakes servo
Servo airbrakes_servo;

int airbrakes_state(double data[]) {
	return_code ret_code;

	if(firstIteration == true){
		//Airbrakes servo
		pinMode(AIRBRAKES_SERVO_PIN, OUTPUT);
		airbrakes_servo.attach(AIRBRAKES_SERVO_PIN);
		firstIteration = false;
	}

	//Updats dt
	time_new = micros();
	dt = (float)(time_new - time_old);
	dt /= (float)1000000; // converted to seconds

	kalman(estimates, data[ALTITUDE], data[ACC_Z], dt, reference_v);
	// write kalman values to file
	reference_v = getReferenceVelocity(estimates[0]);
	error = reference_v - estimates[1];
	u += controller(&error, &parameters, &riemann_sum, dt); //updates controll signal
	time_old = time_new;
	// write error and controll signal too file before if statement
	if(u >= 0 && u <= 180) {
		airbrakes_servo.write(u); //updates servo position
	}

    // remmember to update this to correct tests
	if () {
		ret_code = NEXT;
	}
	else {
		ret_code = REPEAT;
	}

	return ret_code;
}