#include "gps.h"

GPS* gps = 0;

void setup() {
  Serial.begin(11250);
  gps = &GPS::getInstance();
  gps->setUpdateRate(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
}

void serialEvent4()
/* This function is called every time new GPS-data is 
   available at the Serial4 port */
{
    unsigned long start = millis();
    do 
    {
        while (Serial4.available())
          gps->encode(Serial4.read());
    } while (millis() - start < GPS_MAX_WAIT_MILLI);
  Serial.printf("Latitude: %f, Longditude: %f, Altitude: %f, Speed: %f\n\r", gps->getLatitude(), gps->getLongitude(), gps->getAltitude(), gps->getSpeed());     
}
