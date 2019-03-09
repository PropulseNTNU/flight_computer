#include "apogee_detect.hpp"
using namespace std;

double totalLinAcceleration (double data[]) {
    return Sqrt(Sq(data[LINEAR_ACCEL_X])+Sq(LINEAR_ACCEL_Y)+Sq(LINEAR_ACCEL_Z));
}

void updateArray(double* altitudes, double input) {
    double current;
    for (int i = 0; i < 10; i++) {
        current = altitudes[i];
        altitudes[i] = input;
        input = current;
        
    }
}

double returnMax(double* anArray) {
    double max = -1;
    for (int i = 0; i < 10; i++) {
        if (anArray[i] > max) {
            max = anArray[i];
        }
    }
    return max;
}

double returnRange(double* anArray) {
    double min = 9999;
    for (int i = 0; i < 10; i++) {
        if (anArray[i] < min) {
            min = anArray[i];
        }
    }
    return (returnMax(anArray)-min);
}

double returnAvgDiff(double* anArray) {
    double sumDiff = 0;
    double diff = 0;
    for (int i = 0; i < 9; i++) {
        diff = (anArray[i] - anArray[i+1]);
        if (diff > 0) {
            sumDiff += diff;
        } else {
            sumDiff += -(diff);
        }
    }
    return (sumDiff/10);
}

void updateHeightArray(Array* alt, double currentAlt) {
    updateArray(alt->altitudes, currentAlt);
    alt->arrayLen = 10;
    alt->range = returnRange(alt->altitudes);
    alt->maxAltitude = returnMax(alt->altitudes);
    alt->averageDiff = returnAvgDiff(alt->altitudes);
    
}

void printArray(double* array, int length) {
    /*
    for (int n = 0; n < length; n++) {
        cout << array[n];
    }
    cout << endl;
    */
}

void printHeightArray(Array alt) {
    /*
    cout << "Max H: " << alt.maxAltitude << endl;
    cout << "Average diff: " << alt.averageDiff << endl;
    cout << "Range: " << alt.range << endl;
    printArray(alt.altitudes, alt.arrayLen);
     */
}
