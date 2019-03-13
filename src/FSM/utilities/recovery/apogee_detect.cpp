#include "apogee_detect.h"
#include "Arduino.h"
using namespace std;

/*
 Various constants used in ApogeeDetect function
 */



double totalLinAcceleration (double* data) {
    return sqrt(sq(data[LINEAR_ACCEL_X])+sq(LINEAR_ACCEL_Y)+sq(LINEAR_ACCEL_Z));
}

void updateArray(double* altitudes, double input) {
    double current;
    for (int i = 0; i < ARRAY_LEN; i++) {
        if (isnan(input)) {
            input = altitudes[i+1];
        }
        current = altitudes[i];
        altitudes[i] = input;
        input = current;
    }
}

void updateApogeeData(double* apogeeDataArray, double* altitudes) {
    double sumDiff = 0;
    double diff = 0;
    double sumAlt = 0;
    double min = 999999999;
    double max = -1;
    for (int i = 0; i < ARRAY_LEN; i++) {
        if (altitudes[i] > max) {
            max = altitudes[i];
        }
        if (altitudes[i] < min) {
            min = altitudes[i];
        }
        if (i < ARRAY_LEN-1) {
            diff = (altitudes[i] - altitudes[i+1]);
            if (diff > 0) {
                sumDiff += diff;
            } else {
                sumDiff += -(diff);
            }
        }
        sumAlt += altitudes[i];
    }
    apogeeDataArray[AVERAGE_ALTITUDE] = sumAlt/ARRAY_LEN;
    apogeeDataArray[RANGE] = max-min;
    apogeeDataArray[AVERAGE_DIFF] = sumDiff/ARRAY_LEN;
    
    if (apogeeDataArray[AVERAGE_ALTITUDE] > apogeeDataArray[MAX_ALTITUDE]) {
        apogeeDataArray[MAX_ALTITUDE] = apogeeDataArray[AVERAGE_ALTITUDE];
    }
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
            apogee->apogeeData[TIMESTAMP_APOGEE] = data[TIMESTAMP];
            return true;
        } else {
            if (totalLinAcceleration(data) < APOGEE_ACC_VAL/2) { //Very low acc -> timer length halved
                if (apogee->timerEnabled && (data[TIMESTAMP] - apogee->apogeeData[TIMESTAMP_BEGIN] > TIMER_LENGTH/3)) {
                    apogee->apogeeData[TIMESTAMP_APOGEE] = data[TIMESTAMP];
                    return true;
                }
            } else { //Timer elapsed? Apogee.
                if (apogee->timerEnabled && (data[TIMESTAMP] - apogee->apogeeData[TIMESTAMP_BEGIN] > TIMER_LENGTH)) {
                    apogee->apogeeData[TIMESTAMP_APOGEE] = data[TIMESTAMP];
                    return true;
                }
            }
        }
    }
    return false;
}


void printArray(double* array) {
    for (int n = 0; n < ARRAY_LEN; n++) {
        Serial.print(array[n]);
        Serial.print("\t");
    }
    Serial.println("");
}

void printApogeeArray(ApogeeArray alt) {
    Serial.print("Max H: ");
    Serial.println(alt.apogeeData[MAX_ALTITUDE]);
    Serial.print("Average altitude: ");
    Serial.println(alt.apogeeData[AVERAGE_ALTITUDE]);
    Serial.print("Average diff: ");
    Serial.println(alt.apogeeData[AVERAGE_DIFF]);
    Serial.print("Range: ");
    Serial.println(alt.apogeeData[RANGE]);
    printArray(alt.altitudes);
}
