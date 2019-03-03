#ifndef SERIAL_READER_H
#define SERIAL_READER_H
//#include <BasicLinearAlgebra.h>

void parseData();
void recvWithStartEndMarkers();
bool updateSensorData(double* sensor_data);


#endif