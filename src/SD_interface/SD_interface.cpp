#include "SD_interface.h"

File dataFile;

String createDataString(double data[NUM_TYPES]){
  String dataString = "";

  for (int i = 0; i < NUM_TYPES; i++){
    dataString += String(data[i]);
    dataString += ",";
  }

  return dataString;
}

void write_data(double data[NUM_TYPES], const char* fileName) {
    dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
   		dataFile.println(createDataString(data));
    }
    else {
    Serial.println("Error opening file");
    }
    dataFile.close();
}
