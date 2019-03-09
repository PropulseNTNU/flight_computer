#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include "Adafruit_BNO055/Adafruit_BNO055.h"
#include "BME280/SparkFunBME280.h"
#include "sensor_data.h"

const uint8_t IMU_ADDRESS = 0x28;

/*
    Initialization of the BME and IMU sensor
    BME sensor initial address 0x77, if jumper is added address is 0x76
 */
extern BME280 Bme;
extern Adafruit_BNO055 IMU;

/*
    Note that the IMU has declared x axis as the yaw axis, the y axis as the
    pitch axis and the z axis as the roll axis. This is corrected as:
      roll  = x axis
      pitch = y axis
      yaw   = z axis
*/
void readSensors(double *data);
#endif