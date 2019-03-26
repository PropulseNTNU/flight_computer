#ifndef apogee_detect_h
#define apogee_detect_h
#include "../../states.h"
#include <math.h>

#define ARRAY_LEN 5
#define APOGEE_ACC_VAL 1.5  //Lowest value from simulations at ~0.8
#define TIMER_LENGTH 3000
#define APOGEE_ALTITUDE_MARGIN 5
#define RECOVERY_DATA_LEN 6

//Remember to change RECOVERY_DATA_LEN
/*
enum apogeeEnum {
	MAX_ALTITUDE, AVERAGE_ALTITUDE, TOTAL_ACC, TOTAL_ACC_APOGEE, TIMESTAMP_BEGIN_TIMER, TIMESTAMP_APOGEE, TIMESTAMP_DROGUE, TIMESTAMP_MAIN, NUM_REC_DATA
};
*/

enum apogeeEnum {
	MAX_ALTITUDE, AVERAGE_ALTITUDE, TIMESTAMP_BEGIN_TIMER, TIMESTAMP_APOGEE, TIMESTAMP_DROGUE, TIMESTAMP_MAIN, NUM_REC_DATA
};



struct ApogeeArray {
    double altitudes[ARRAY_LEN] = {0};
    double recoveryData[NUM_REC_DATA] = {0};
    bool timerEnabled = false;
    void updateDataArray(ApogeeArray* alt, double input_altitude);
};
typedef ApogeeArray AltitudeStruct;

//Returns the magnitude of measured (proper) acceleration in x,y,z.
double totalAcceleration(double data[]); 

//Pushes input into altitudes[10] array and removes the last. (FIFO)
void updateArray(double* array_first, double input);

//Updates the apogeeData[] array by checking altitudes[10] array.
void updateApogeeData(double* apogeeDataArray, double* altitudes);

//Print functions for testing.
void printArray(double* array);
void printApogeeArray(ApogeeArray alt);


/*
 This is the function that detects apogee in airbrakes_state. It is based on checking for low acceleraion, ~1, and then detects apogee when the average current altitude drops below max altitude.
 
 (Option to integrate ACC_Y over time rejected due to uncertainties in measurements without filter. Might evaluate after test flight data)
 
 Redundancy: A timer is started when low acceleration is detected, where apogee is detected after 3 seconds. If we detect very low acc, (~1)/2, then apogee is detected after 1 second.
*/
bool apogeeDetected(ApogeeArray* apogee, double* data, int enable_acc);

bool apogeeDetected(ApogeeArray* apogee, double* data);



#endif /* apogee_detect_hpp */
