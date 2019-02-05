/*
  This arduino program is currently doing the following:
    1. Initializing sensor objects and log file.
    2. Setting up serial and i2c communication with sensors and SD.
    3. Setting up the BME280 altitude sensor.
    4. Setting up the BO055 IMU sensor
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
File myFile;
String DataFile = "Datafile.txt";


struct SensorData
 {
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
  //init data struct
  SensorData data;

  //Update BMP280 sensor data
  data.bme_temp = Bme.readTempC();
  data.pressure = Bme.readFloatPressure();
  data.altitude = Bme.readFloatAltitudeMeters();

  //Create IMU sensor event(Do measurements)
  sensors_event_t event; 
  IMU.getEvent(&event);
  
  //Acceleration in m/s^2
  data.acc_x = event.acceleration.x;
  data.acc_y = event.acceleration.y;
  data.acc_z = event.acceleration.z;

  //Rotation in deg
  data.pitch = event.orientation.pitch;
  data.roll = event.orientation.roll;
  data.yaw = event.orientation.heading;

  //Temp IMU deg
  data.IMU_temp = event.temperature;

  //Magnetic vector values in uT
  data.mag_x = event.magnetic.x;
  data.mag_y = event.magnetic.y;
  data.mag_z = event.magnetic.z;
  
  
  //Writing to SD card
  myFile = SD.open("Datafile.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(createDataString(data));
  }
  else {
    Serial.println("Error opening file");
  }
  myFile.close();

  //Uncomment this line when running system
  //delay(BNO055_SAMPLERATE_DELAY_MS);

  delay(200);
}

String createDataString(SensorData data){
  String dataString = "";
  
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
