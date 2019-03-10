#ifndef apogee_detect_h
#define apogee_detect_h
#include "../../states.h"



enum apogeeEnum {RANGE, MAX_ALTITUDE, AVERAGE_DIFF, AVERAGE_ALTITUDE, TIMESTAMP_BEGIN, ARRAY_LENGTH, NUM_DATA};

struct ApogeeArray {
    double altitudes[10] = {0,0,0,0,0,0,0,0,0,0};
    double apogeeData[NUM_DATA] = {0,0,0,0,0,10};
    bool timerEnabled = false;
    void updateApogeeArray(ApogeeArray* alt, double currentAlt);
};

double totalLinAcceleration(double data[]);

void updateArray(double* array_first, double input);
void updateApogeeData(double* apogeeDataArray, double* altitudes);

void printArray(double* array, int length);
void printApogeeArray(ApogeeArray alt);

bool apogeeDetected(ApogeeArray* apogee, double* data);



#endif /* apogee_detect_hpp */
