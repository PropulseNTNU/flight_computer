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

void write_SD(double data[NUM_TYPES]) {
  if (dataFile) {
    dataFile.println(createDataString(data));
    dataFile.flush();
  }
  else {
    Serial.println("Error opening file");
  }
}

bool init_SD(const char* fileName){
  dataFile = SD.open(fileName, O_CREAT | O_WRITE);
  if(dataFile){
    return true;
  }
  return false;
}


void close_SD() {
  dataFile.close();
}
