#ifndef SERIAL_READER_H
#define SERIAL_READER_H


void parseData(double * sensor_data);
void recvWithStartEndMarkers();
bool updateSensorData(double* sensor_data);


#endif
