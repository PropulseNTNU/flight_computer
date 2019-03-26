#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

/*
  NB: ACC_X,Y,Z contains linear acceleration + gravity
    GRAVITY_ACCEL_X, Y, Z contains only gravity components
    LINEAR_ACCEL_X,Y,Z contains ONLY linear accelerations.

  Angular velocities in dps per now.
*/
enum sensorData { TIMESTAMP, BME_TEMP, IMU_TEMP, 
                  PRESSURE, ALTITUDE, 
                  ACC_X, ACC_Y, ACC_Z, 
                  ROLL, PITCH, YAW, 
                  MAG_X, MAG_Y, MAG_Z,
                  ANGULAR_VEL_X,ANGULAR_VEL_Y,ANGULAR_VEL_Z,
                  GRAVITY_ACC_X,GRAVITY_ACC_Y,GRAVITY_ACC_Z, 
                  LINEAR_ACCEL_X,LINEAR_ACCEL_Y,LINEAR_ACCEL_Z,
                  QUATERNION_X, QUATERNION_Y, QUATERNION_Z, QUATERNION_W,
                  STATE, ALTITUDE_GPS, LONGITUDE_GPS, LATITUDE_GPS, AIRBRAKES_SERVO_POS, NUM_TYPES
              };

#endif