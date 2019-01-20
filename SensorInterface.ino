/*
  This arduino program is currently doing the following:
    1. Setting up serial and i2c communication
    2. Setting up the BME280 altitude sensor and printing the desired sensor information
*/

#include <Wire.h>
#include "src/LED/LED.h"
#include "src/BME280/SparkFunBME280.h"

//Setting up objects and params
BME280 Bme;
int const diode = 13;

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

  //Successfull setup lights diode
  LEDConfig(diode);
  LEDSetMode(diode, HIGH);
}

void loop()
{

  Bme.printSensorInformation(true,true,true,false);

  delay(100);
}
