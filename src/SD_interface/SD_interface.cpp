#include "SD_interface.h"

File files[NUM_FILES];

unsigned long logIntervals[NUM_INTERVALS] = {10, 10, 100, 1000};
unsigned long lastLog[NUM_LASTLOGS];

String createDataString(double* data, int len){
  String dataString = "";
  for (int i = 0; i < len; i++){
    dataString += String(data[i]);
    dataString += ",";
  }
  return dataString;
}

void write_SD(int file, double* data, int len) {
  if (files[file]) {
    files[file].println(createDataString(data, len));
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

unsigned long* getLogInterval(int interval) {
    return &logIntervals[interval];
}

unsigned long* getLastLog(int lastLogType) {
    return &lastLog[lastLogType];
}

void setLastLog(unsigned long newLastLog, int lastLogType) {
    lastLog[lastLogType] = newLastLog;
}
