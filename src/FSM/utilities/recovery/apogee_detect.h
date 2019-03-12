#ifndef apogee_detect_h
#define apogee_detect_h
#include "../../states.h"
#include <math.h>

#define ARRAY_LEN 5
#define APOGEE_ACC_VAL 0.6
#define TIMER_LENGTH 3000
#define APOGEE_ALTITUDE_MARGIN 5

enum apogeeEnum {RANGE, MAX_ALTITUDE, AVERAGE_DIFF, AVERAGE_ALTITUDE, TIMESTAMP_BEGIN, ARRAY_LENGTH, NUM_DATA};

struct ApogeeArray {
    double altitudes[ARRAY_LEN] = {0};
    double apogeeData[NUM_DATA] = {0,0,0,0,0,ARRAY_LEN};
    bool timerEnabled = false;
    void updateApogeeArray(ApogeeArray* alt, double currentAlt);
};
typedef ApogeeArray AltitudeStruct;

double totalLinAcceleration(double data[]);

void updateArray(double* array_first, double input);
void updateApogeeData(double* apogeeDataArray, double* altitudes);

void printArray(double* array);
void printApogeeArray(ApogeeArray alt);

bool apogeeDetected(ApogeeArray* apogee, double* data);



#endif /* apogee_detect_hpp */
