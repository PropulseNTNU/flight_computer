#include "apogee_detect.h"
#include "Arduino.h"
using namespace std;

double totalLinAcceleration (double data[]) {
    return sqrt(sq(data[LINEAR_ACCEL_X])+sq(LINEAR_ACCEL_Y)+sq(LINEAR_ACCEL_Z));
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

void ApogeeArray::updateApogeeArray(ApogeeArray* alt, double currentAlt) {
    updateArray(alt->altitudes, currentAlt);
    alt->arrayLen = 10;
    alt->range = returnRange(alt->altitudes);
    alt->maxAltitude = returnMax(alt->altitudes);
    alt->averageDiff = returnAvgDiff(alt->altitudes);
    
}

void printArray(double* array, int length) {
    /*
    for (int n = 0; n < length; n++) {
        Serial.print(array[n]);
    }
    Serial.println("");
     */
    /*
    for (int n = 0; n < length; n++) {
        cout << array[n];
    }
    cout << endl;
    */
}

void printApogeeArray(ApogeeArray alt) {
    Serial.print("Max H: ");
    Serial.println(alt.maxAltitude);
    Serial.print("Average diff: ");
    Serial.println(alt.averageDiff);
    Serial.print("Range: ");
    Serial.println(alt.range);
    printArray(alt.altitudes, alt.arrayLen);
    /*
    cout << "Max H: " << alt.maxAltitude << endl;
    cout << "Average diff: " << alt.averageDiff << endl;
    cout << "Range: " << alt.range << endl;
    printArray(alt.altitudes, alt.arrayLen);
     */
}
