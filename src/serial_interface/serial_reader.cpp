#include <Arduino.h>
#include <string.h>
#include <stdlib.h> 
#include "serial_reader.h"

const int numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

bool newData = false;

void parseData(double * sensor_data) {      // split the data into its parts

    char * strtokIndx = strtok(tempChars,",");   // this is used by strtok() as an index
    int i = 0;
    while(strtokIndx != NULL) {
      sensor_data[i] = atof(strtokIndx);
      strtokIndx = strtok(NULL, ",");
      i += 1;
    }
    
}

void recvWithStartEndMarkers() {
    static bool recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

bool updateSensorData(double * sensor_data){
  recvWithStartEndMarkers();
  if (newData == true) {
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() used in parseData() replaces the commas with \0
      parseData(sensor_data);
      newData = false;
      return true;
  }
  return false;
}
