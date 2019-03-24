#include "apogee_detect.h"
#include "Arduino.h"
using namespace std;

/*
 Various constants used in ApogeeDetect function
 */


//Function not in use
double totalLinAcceleration (double* data) {
    return sqrt(sq(data[LINEAR_ACCEL_X])+sq(data[LINEAR_ACCEL_Y])+sq(data[LINEAR_ACCEL_Z]));
}

double totalAcceleration(double* data) {
    return sqrt(sq(data[ACC_X])+sq(data[ACC_Y])+sq(data[ACC_Z]));
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
    for (int i = 0; i < ARRAY_LEN; i++) {
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
    apogeeDataArray[AVERAGE_DIFF] = sumDiff/ARRAY_LEN;
    
    if (apogeeDataArray[AVERAGE_ALTITUDE] > apogeeDataArray[MAX_ALTITUDE]) {
        apogeeDataArray[MAX_ALTITUDE] = apogeeDataArray[AVERAGE_ALTITUDE];
    }
}

void ApogeeArray::updateDataArray(ApogeeArray* alt, double* data) {
    updateArray(alt->altitudes, data[ALTITUDE]);
    updateApogeeData(alt->recoveryData, alt->altitudes);
    alt->recoveryData[TOTAL_ACC] = totalAcceleration(data);
}


//Option to add Average difference condition.
bool apogeeDetected(ApogeeArray* apogee, double* data, int enable_acc) {
    double accMagnitude = totalAcceleration(data); //Magnitude of acceleration in x,y,z
    if (accMagnitude < APOGEE_ACC_VAL ) { //Checks for low acceleration
        if (apogee->timerEnabled == false) { //Start timer
            apogee->recoveryData[TIMESTAMP_BEGIN_TIMER] = data[TIMESTAMP];
            apogee->timerEnabled = true;
        }
        if ((apogee->recoveryData[MAX_ALTITUDE] - apogee->recoveryData[AVERAGE_ALTITUDE]) < APOGEE_ALTITUDE_MARGIN) { //Descending -> apogee
            apogee->recoveryData[TIMESTAMP_APOGEE] = data[TIMESTAMP];
            apogee->recoveryData[TOTAL_ACC_APOGEE] = accMagnitude;
            return true;
        } else {
            if (accMagnitude < APOGEE_ACC_VAL/2) { //Very low acc -> timer length reduced to a third
                if (apogee->timerEnabled && (data[TIMESTAMP] - apogee->recoveryData[TIMESTAMP_BEGIN_TIMER] > TIMER_LENGTH/3)) {
                    apogee->recoveryData[TIMESTAMP_APOGEE] = data[TIMESTAMP];
                    apogee->recoveryData[TOTAL_ACC_APOGEE] = accMagnitude;
                    return true;
                }
            } else { //Timer elapsed? Apogee.
                if (apogee->timerEnabled && (data[TIMESTAMP] - apogee->recoveryData[TIMESTAMP_BEGIN_TIMER] > TIMER_LENGTH)) {
                    apogee->recoveryData[TIMESTAMP_APOGEE] = data[TIMESTAMP];
                    apogee->recoveryData[TOTAL_ACC_APOGEE] = accMagnitude;
                    return true;
                }
            }
        }
    }
    return false;
}


bool apogeeDetected(ApogeeArray* apogee, double* data) {
    if ((apogee->recoveryData[MAX_ALTITUDE] - apogee->recoveryData[AVERAGE_ALTITUDE]) > APOGEE_ALTITUDE_MARGIN) { //Descending -> apogee
        apogee->recoveryData[TIMESTAMP_APOGEE] = data[TIMESTAMP];
        apogee->recoveryData[TOTAL_ACC_APOGEE] = totalAcceleration(data);
        return true;
    } else {
        return false;
    }
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
    Serial.println(alt.recoveryData[MAX_ALTITUDE]);
    Serial.print("Average altitude: ");
    Serial.println(alt.recoveryData[AVERAGE_ALTITUDE]);
    Serial.print("Average diff: ");
    Serial.println(alt.recoveryData[AVERAGE_DIFF]);
    printArray(alt.altitudes);
}