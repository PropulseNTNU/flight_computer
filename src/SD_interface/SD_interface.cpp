#include "SD_interface.h"

File files[NUM_FILES];

String createDataString(double* data){
  String dataString = "";

  for (int i = 0; i < NUM_TYPES; i++){
    dataString += String(data[i]);
    dataString += ",";
  }

  return dataString;
}

void write_SD(int file, double* data) {
  if (files[file]) {
    files[file].println(createDataString(data));
    files[file].flush();
  }
  else {
    Serial.print("Error writing to file: ");
    Serial.println(file);
  }
}

bool init_SD(int file, const char* fileName){
  files[file] = SD.open(fileName, O_CREAT | O_WRITE);
  if(files[file]){
    return true;
  }
  return false;
}

void close_SD() {
  for(int i = 0; i < NUM_FILES; i++){
    files[i].close();
  }
}
