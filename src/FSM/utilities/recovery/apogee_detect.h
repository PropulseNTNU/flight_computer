#ifndef apogee_detect_h
#define apogee_detect_h
#include "../../states.h"
#include <math.h>

#define ARRAY_LEN 10
#define APOGEE_ACC_VAL 1.5  //Lowest value from simulations at ~0.8
#define TIMER_LENGTH 3000
#define APOGEE_ALTITUDE_MARGIN 5
#define RECOVERY_DATA_LEN 10

enum apogeeEnum {
    RANGE, MAX_ALTITUDE, AVERAGE_DIFF, AVERAGE_ALTITUDE, TOTAL_LIN_ACC, TOTAL_LIN_ACC_APOGEE, TIMESTAMP_BEGIN_TIMER, TIMESTAMP_APOGEE, TIMESTAMP_DROGUE, TIMESTAMP_MAIN, NUM_DATA
};

struct ApogeeArray {
    double altitudes[ARRAY_LEN] = {0};
    double recoveryData[NUM_DATA] = {0};
    bool timerEnabled = false;
    void updateDataArray(ApogeeArray* alt, double* data);
};
typedef ApogeeArray AltitudeStruct;



//Returns the magnitude of measured acceleration in x,y,z, while factoring out gravitational acceleration.
double totalLinAcceleration(double data[]);     //Important: Check if IMU returns the expected values during test flight.

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
bool apogeeDetected(ApogeeArray* apogee, double* data);



#endif /* apogee_detect_hpp */
