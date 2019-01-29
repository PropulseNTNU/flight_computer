/*
  This arduino program is currently doing the following:
    1. Setting up serial and i2c communication
    2. Setting up the BME280 altitude sensor and printing the desired sensor information
*/

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "src/LED/LED.h"
#include "src/BME280/SparkFunBME280.h"
#include "src/Adafruit_BNO055/Adafruit_BNO055.h"

//Setting up objects and params
BME280 Bme;
int const diode = 13;
uint8_t const SD_cspin = BUILTIN_SDCARD;
File myFile;
String DataFile = "Datafile.txt";
struct SensorData {
  float temp;
  float pressure;
  float altitude;
};

void setup()
{
  //Setup serial connection
  Serial.begin(9600);
  
  //Start I2C
  Wire.begin();

  //Starting communication with BME280 using I2C
  Serial.println("Reading basic values from BME280");
  if (!Bme.beginI2C())
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

  //Successfull setup lights diode
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
  data.temp = Bme.readTempC();
  data.pressure = Bme.readFloatPressure();
  data.altitude = Bme.readFloatAltitudeMeters();
  
  //Writing to SD card
  myFile = SD.open("Datafile.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(createDataString(data));
  }
  else {
    Serial.println("Error opening file");
  }
  myFile.close();
  
  Bme.printSensorInformation(true,true,true,false);
  delay(100);
}

String createDataString(SensorData data){
  String dataString = "";
  dataString += String(data.temp);
  dataString += ",";
  dataString += String(data.pressure);
  dataString += ",";
  dataString += String(data.altitude);
  return dataString;
}
