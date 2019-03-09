#ifndef apogee_detect_h
#define apogee_detect_h
#include "../../states.h"

struct ApogeeArray {
    double altitudes[10] = {0,0,0,0,0,0,0,0,0,0};
    double arrayLen = 10;
    double range = 0;
    double maxAltitude = 0;
    double averageDiff = 0;
    void updateApogeeArray(ApogeeArray* alt, double currentAlt);
};

double totalLinAcceleration(double data[]);

void printArray(double* array, int length);
void updateArray(double* array_first, double input);

double returnMax(double* anArray);
double returnRange(double* anArray);
double returnAvgDiff(double* anArray);

void printApogeeArray(ApogeeArray alt);





#endif /* apogee_detect_hpp */
