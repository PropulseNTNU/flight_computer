#ifndef apogee_detect_h
#define apogee_detect_h
#include "../../states.h"
#include <math.h>

#define ARRAY_LEN 5
#define APOGEE_ACC_VAL 1.5  //Lowest value from simulations at ~0.8
#define TIMER_LENGTH 3000
#define APOGEE_ALTITUDE_MARGIN 3
#define RECOVERY_DATA_LEN 6

enum apogeeEnum {
	MAX_ALTITUDE, AVERAGE_ALTITUDE, TIMESTAMP_BEGIN_TIMER, TIMESTAMP_APOGEE, TIMESTAMP_DROGUE, TIMESTAMP_MAIN, NUM_REC_DATA
};

//AltitudeStruct an alias for ApogeeArray in drogue and main chute states.
typedef struct ApogeeArray {
    double altitudes[ARRAY_LEN] = {0};
    double recoveryData[NUM_REC_DATA] = {0};
    bool timerEnabled = false;
    void updateDataArray(ApogeeArray* alt, double input_altitude);
} AltitudeStruct;

// Pushes input into altitudes[10] array and removes the last. (FIFO)
void updateArray(double* array_first, double input);

// Updates the apogeeData[] array by checking altitudes[10] array.
void updateApogeeData(double* apogeeDataArray, double* altitudes);

// Apogee function that controls the state transition between airbrakes and apogee.
bool apogeeDetected(ApogeeArray* apogee, double* data);

/*

//Print functions for testing.
void printArray(double* array);
void printApogeeArray(ApogeeArray alt);


Section below can be used to detect apogee using a combination of total acceleration and altitude.

enum apogeeEnum {
	MAX_ALTITUDE, AVERAGE_ALTITUDE, TOTAL_ACC, TOTAL_ACC_APOGEE, TIMESTAMP_BEGIN_TIMER, TIMESTAMP_APOGEE, TIMESTAMP_DROGUE, TIMESTAMP_MAIN, NUM_REC_DATA
};

//Returns the magnitude of measured (proper) acceleration in x,y,z.
double totalAcceleration(double data[]); 


This is the function that detects apogee in airbrakes_state. It is based on checking for low acceleraion, ~1, and then detects apogee when the average current altitude drops below max altitude.
 
(Option to integrate ACC_Y over time rejected due to uncertainties in measurements without filter. Might evaluate after test flight data)
 
Redundancy: A timer is started when low acceleration is detected, where apogee is detected after 3 seconds. If we detect very low acc, (~1)/2, then apogee is detected after 1 second.

bool apogeeDetected(ApogeeArray* apogee, double* data, int enable_acc);

*/

#endif /* apogee_detect_hpp */
