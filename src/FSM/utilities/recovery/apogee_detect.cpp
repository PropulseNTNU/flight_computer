#include "apogee_detect.h"
#include "Arduino.h"
using namespace std;

/*
 Various constants used in ApogeeDetect function
 */

const double APOGEE_ACC_VAL = 0.3;
const double TIMER_LENGTH = 3000;
const double APOGEE_ALTITUDE_MARGIN = 10;

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

void updateApogeeData(double* apogeeDataArray, double* altitudes) {
    double sumDiff = 0;
    double diff = 0;
    double min = 999999999;
    double max = -1;
    for (int i = 0; i < 10; i++) {
        if (altitudes[i] > apogeeDataArray[MAX_ALTITUDE]) {
            apogeeDataArray[MAX_ALTITUDE] = altitudes[i];
        }
        if (altitudes[i] > max) {
            max = altitudes[i];
        }
        if (altitudes[i] < min) {
            min = altitudes[i];
        }
        if (i < 9) {
            diff = (altitudes[i] - altitudes[i+1]);
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
    updateApogeeData(alt->apogeeData, alt->altitudes);
}

//Option to add Average difference condition - just need to experiment first.
bool apogeeDetected(ApogeeArray* apogee, double* data) {
    if (totalLinAcceleration(data) < APOGEE_ACC_VAL ) { //Checks for low acceleration
        if (apogee->timerEnabled == false) { //Start timer
            apogee->apogeeData[TIMESTAMP_BEGIN] = data[TIMESTAMP];
            apogee->timerEnabled = true;
        }
        if ((apogee->apogeeData[MAX_ALTITUDE] - apogee->apogeeData[AVERAGE_ALTITUDE]) < APOGEE_ALTITUDE_MARGIN) { //Descending -> apogee
            return true;
        } else {
            if (totalLinAcceleration(data) < APOGEE_ACC_VAL/2) { //Very low acc -> timer length halved
                if (apogee->timerEnabled && (data[TIMESTAMP] - apogee->apogeeData[TIMESTAMP_BEGIN] > TIMER_LENGTH/2)) {
                    return true;
                }
            } else { //Timer elapsed? Apogee.
                if (apogee->timerEnabled && (data[TIMESTAMP] - apogee->apogeeData[TIMESTAMP_BEGIN] > TIMER_LENGTH)) {
                    return true;
                }
            }
        }
    }
    return false;
}


void printArray(double* array, int length) {
    for (int n = 0; n < length; n++) {
        Serial.print(array[n]);
        Serial.print("\t");
    }
    Serial.println("");
}

void printApogeeArray(ApogeeArray alt) {
    Serial.print("Max H: ");
    Serial.println(alt.apogeeData[MAX_ALTITUDE]);
    Serial.print("Average diff: ");
    Serial.println(alt.apogeeData[AVERAGE_DIFF]);
    Serial.print("Range: ");
    Serial.println(alt.apogeeData[RANGE]);
    printArray(alt.altitudes, 10);
}
