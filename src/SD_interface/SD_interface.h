#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

#include <SD.h>
#include "../sensor_interface/sensor_data.h"


String createDataString(double data[NUM_TYPES]);

void write_data(double* data, const char* fileName);

#endif