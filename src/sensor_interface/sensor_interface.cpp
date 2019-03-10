#include "sensor_interface.h"
using namespace std;

/*
    Initialization of the BME and IMU sensor
    BME sensor initial address 0x77, if jumper is added address is 0x76
 */
BME280 Bme;
Adafruit_BNO055 IMU = Adafruit_BNO055(100, IMU_ADDRESS);

GPS* gps = &GPS::getInstance();

BME280* get_BME(){
  return &Bme;
}

Adafruit_BNO055* get_IMU(){
  return &IMU;
}


GPS* get_GPS() {
  return gps;
}

/*
    Note that the IMU has declared x axis as the yaw axis, the y axis as the
    pitch axis and the z axis as the roll axis. This is corrected as:
      roll  = x axis
      pitch = y axis
      yaw   = z axis
*/

void readSensors(double *data){
  //Update BMP280 sensor data
  data[BME_TEMP] = Bme.readTempC();
  data[PRESSURE] = Bme.readFloatPressure();
  data[ALTITUDE] = Bme.readFloatAltitudeMeters();

  //Temp IMU deg
  data[IMU_TEMP] = IMU.getTemp();

  //Extract Acceleration in m/s^2
  imu::Vector<3> accel = IMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  data[ACC_X] = accel.x();
  data[ACC_Y] = accel.y();
  data[ACC_Z] = accel.z();
  
  //Extract magnetometer data in uT
  imu::Vector<3> mag = IMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  data[MAG_X] = mag.x();
  data[MAG_Y] = mag.y();
  data[MAG_Z] = mag.z();

  //Extract euler angles in deg
  imu::Vector<3> euler = IMU.getVector(Adafruit_BNO055::VECTOR_EULER);
  data[ROLL] = euler.z();
  data[PITCH] = euler.y();
  data[YAW] = euler.x();

  //Extract angular rates in dps
  imu::Vector<3> rates = IMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  data[ANGULAR_VEL_X] = rates.z();
  data[ANGULAR_VEL_Y] = rates.y();
  data[ANGULAR_VEL_Z] = rates.x();

  //Extract gravity components
  imu::Vector<3> gravity = IMU.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  data[GRAVITY_ACC_X] = gravity.x();
  data[GRAVITY_ACC_Y] = gravity.y();
  data[GRAVITY_ACC_Z] = gravity.z();

  //linear acceleration = acceleration - gravity
  imu::Vector<3> linear_accel = IMU.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  data[LINEAR_ACCEL_X] = linear_accel.x();
  data[LINEAR_ACCEL_Y] = linear_accel.y();
  data[LINEAR_ACCEL_Z] = linear_accel.z();

  //Extract unit quaternions
  imu::Quaternion quaternions = IMU.getQuat(); 
  data[QUATERNION_X] = quaternions.x();
  data[QUATERNION_Y] = quaternions.y();
  data[QUATERNION_Z] = quaternions.z();
  data[QUATERNION_W] = quaternions.w();

  // Fetch GPS data
  data[ALTITUDE_GPS] = gps->getAltitude();
  data[LONGITUDE_GPS] = gps->getLongitude();
  data[LATITUDE_GPS] = gps->getLatitude();
  
  //data[TIMESTAMP]= event.timestamp;
  data[TIMESTAMP] = millis();
}