#include "apogee_detect.h"
#include "Arduino.h"
using namespace std;

const double APOGEE_ACC_VAL = 0.3;

double totalLinAcceleration (double* data) {
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

void updateApogeeData(double* apogeeDataArray) {
    double sumDiff = 0;
    double diff = 0;
    double min = 9999;
    double max = 0;
    for (int i = 0; i < 10; i++) {
        if (apogeeDataArray[i] > apogeeDataArray[MAX_ALTITUDE]) {
            apogeeDataArray[MAX_ALTITUDE] = apogeeDataArray[i];
        }
        if (apogeeDataArray[i] > max) {
            max = apogeeDataArray[i];
        }
        if (apogeeDataArray[i] < min) {
            min = apogeeDataArray[i];
        }
        if (i <= 9) {
            diff = (apogeeDataArray[i] - apogeeDataArray[i+1]);
            if (diff > 0) {
                sumDiff += diff;
            } else {
                sumDiff += -(diff);
            }
        }
    }
    apogeeDataArray[RANGE] = max-min;
    apogeeDataArray[AVERAGE_DIFF] = sumDiff/10;
}

void ApogeeArray::updateApogeeArray(ApogeeArray* alt, double currentAlt) {
    updateArray(alt->altitudes, currentAlt);
    updateApogeeData(alt->apogeeData);
}

//TIMESTAMP IN DATA ARRAY
bool apogeeDetected(ApogeeArray* apogee, double* data) { //BEST OPTION TO TRIGGER A TIMER (if second test never satisfied.)
    if ((totalLinAcceleration(data) < APOGEE_ACC_VAL) && (apogee->apogeeData[AVERAGE_DIFF] < 10)) {
        if ((apogee->apogeeData[MAX_ALTITUDE] - apogee->apogeeData[AVERAGE_ALTITUDE]) < 10) {
            return true;
        }
    }
    return false;
}


void printArray(double* array, int length) {
    for (int n = 0; n < length; n++) {
        Serial.print(array[n]);
    }
    Serial.println("");
    /*
    for (int n = 0; n < length; n++) {
        cout << array[n];
    }
    cout << endl;
    */
}

void printApogeeArray(ApogeeArray alt) {
    Serial.print("Max H: ");
    Serial.println(alt.apogeeData[MAX_ALTITUDE]);
    Serial.print("Average diff: ");
    Serial.println(alt.apogeeData[AVERAGE_DIFF]);
    Serial.print("Range: ");
    Serial.println(alt.apogeeData[RANGE]);
    printArray(alt.altitudes, 10);
    /*
    cout << "Max H: " << alt.maxAltitude << endl;
    cout << "Average diff: " << alt.averageDiff << endl;
    cout << "Range: " << alt.range << endl;
    printArray(alt.altitudes, alt.arrayLen);
     */
}
