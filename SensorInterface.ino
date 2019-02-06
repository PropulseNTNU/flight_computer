/*
  This arduino program is currently doing the following:
    1. Initializing sensor objects and log file.
    2. Setting up serial and i2c communication with sensors and SD.
    3. Setting up the BME280 altitude sensor.
    4. Setting up the BNO055 IMU sensor
    5. Logging the sensor data to the text file on the SD Card.
*/

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "src/LED/LED.h"
#include "src/BME280/SparkFunBME280.h"
#include "src/Adafruit_BNO055/Adafruit_BNO055.h"

//Setting up objects and params
BME280 Bme;
Adafruit_BNO055 IMU = Adafruit_BNO055(100, 0x28);

int const diode = 13;
uint8_t const SD_cspin = BUILTIN_SDCARD;
File dataFile;
String DataFile = "Datafile.txt";

/*
struct SensorData
 {
  int timestamp;
  float bme_temp;
  float IMU_temp;
  float pressure;
  float altitude;
  double acc_x;
  double acc_y;
  double acc_z;
  double pitch;
  double roll;
  double yaw;
  double mag_x;
  double mag_y;
  double mag_z;
};
*/

enum datatype {TIMESTAMP, BME_TEMP, IMU_TEMP, 
                  PRESSURE, ALTITUDE, 
                  ACC_X, ACC_Y, ACC_Z, 
                  PITCH, ROLL, YAW, 
                  MAG_X, MAG_Y, MAG_Z, NUM_TYPES};

//init data struct
//SensorData data;
double data[NUM_TYPES];

void setup()
{
  //Setup serial connection
  Serial.begin(9600);
 
  //Start I2C
  Wire.begin();
  
  Serial.println("Starting I2C communication with BME280");
  if (!Bme.beginI2C())
  {
    Serial.println("The BME sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }

  Serial.println("Starting I2C communication with IMU");
  if (!IMU.begin())
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }

  //Setup SD-card module
  if (!SD.begin(SD_cspin)) {
    Serial.println("initialization failed!");
    delay(1000);
    return;
  }
  else {
    delay(1000);
    Serial.println("SD card module successfully started");
    delay(2000);
    
  }

  //Successfull setup -> lights diode
  LEDConfig(diode);
  LEDSetMode(diode, HIGH);


  //Delete file?
  Serial.println("Type 'd'/'k' to delete or keep log file ");
  
  while(1){
    String answer;
    answer = Serial.read(); 
    if (answer == "d"){
      SD.remove("Datafile.txt");
      break;
    }
    else if (answer == "k") {
      break;
    }
  }
}

void loop()
{ 

  //Update BMP280 sensor data
  data[BME_TEMP] = Bme.readTempC();
  data[PRESSURE] = Bme.readFloatPressure();
  data[ALTITUDE] = Bme.readFloatAltitudeMeters();

  //Create IMU sensor event
  sensors_event_t event; 
  IMU.getEvent(&event);
  
  //Extract sensor fused orientation
  data[PITCH] = event.orientation.pitch;
  data[ROLL] = event.orientation.roll;
  data[YAW] = event.orientation.heading;
  data[TIMESTAMP]= event.timestamp;

  //Temp IMU deg
  data[IMU_TEMP] = event.temperature;

  //Extract "raw" Acceleration in m/s^2
  imu::Vector<3> accel = IMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  data[ACC_X] = accel.x();
  data[ACC_Y] = accel.y();
  data[ACC_Z] = accel.z();
  
  //Extract "raw" magnetometer in uT
  imu::Vector<3> mag = IMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  data[MAG_X] = mag.x();
  data[MAG_Y] = mag.y();
  data[MAG_Z] = mag.z();
  
  //Writing to SD card
  dataFile = SD.open("Datafile.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(createDataString(data));
  }
  else {
    Serial.println("Error opening file");
  }
  dataFile.close();

  delay(500);
  
  
}

String createDataString(double data[NUM_TYPES]){
  String dataString = "";

  for (int i = 0; i < NUM_TYPES; i++){
    dataString += String(data[i]);
    dataString += ",";
  }

  return dataString;
}


/*String createDataString(SensorData data){
  String dataString = "";

  dataString += String(data.timestamp);
  dataString += ",";
  dataString += String(data.bme_temp);
  dataString += ",";
  dataString += String(data.IMU_temp);
  dataString += ",";
  dataString += String(data.pressure);
  dataString += ",";
  dataString += String(data.altitude);
  dataString += ",";
  dataString += String(data.acc_x);
  dataString += ",";
  dataString += String(data.acc_y);
  dataString += ",";
  dataString += String(data.acc_z);
  dataString += ",";
  dataString += String(data.pitch);
  dataString += ",";
  dataString += String(data.roll);
  dataString += ",";
  dataString += String(data.yaw);
  dataString += ",";
  dataString += String(data.mag_x);
  dataString += ",";
  dataString += String(data.mag_y);
  dataString += ",";
  dataString += String(data.mag_z);

  return dataString;
}
*/
