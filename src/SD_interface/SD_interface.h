#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

#include <SD.h>

enum fileEnum {
    DATA_FILE, AIRBRAKES_FILE, NUM_FILES
};

String createDataString(double* data, int len);

void write_SD(int file, double* data, int len);

bool init_SD(int file, const char* fileName);

void close_SD();

#endif