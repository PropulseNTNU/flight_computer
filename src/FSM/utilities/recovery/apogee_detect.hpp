#ifndef apogee_detect_h
#define apogee_detect_h
#include "../../states.h"

typedef struct HeightArray {
    double* altitudes;
    double arrayLen = 10;
    double range;
    double maxAltitude;
    double averageDiff;
    HeightArray updateHeightArray(HeightArray alt_array, double currentAlt);
} Array;

double totalLinAcceleration(double data[]);

double Sq(double data);
double Sqrt(double data);

void printArray(double* array, int length);
void updateArray(double* array_first, double input);

double returnMax(double* anArray);
double returnRange(double* anArray);
double returnAvgDiff(double* anArray);

void updateHeightArray(Array* alt, double currentAlt);
void printHeightArray(Array alt);



#endif /* apogee_detect_hpp */
