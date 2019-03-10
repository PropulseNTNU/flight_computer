#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

#include <SD.h>
#include "../sensor_interface/sensor_data.h"

enum fileEnum {
    DATA_FILE, AIRBRAKES_FILE, NUM_FILES
};

String createDataString(double* data);

void write_SD(int file, double* data);

bool init_SD(int file, const char* fileName);

void close_SD();

#endif