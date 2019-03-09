#ifndef SD_INTERFACE_H
#define SD_INTERFACE_H

#include <SD.h>
#include "../sensor_interface/sensor_data.h"

String createDataString(double data[NUM_TYPES]);

void write_SD(double* data);

bool init_SD(const char* fileName);

void close_SD();

#endif