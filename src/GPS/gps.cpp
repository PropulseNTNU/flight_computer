#include "gps.h"

GPS::GPS() 
{
    buffer = new char* [bufferSentences*82]; // Max length of NMEA sentence is 82 bits
    baudrate = GPS_BAUDRATE;
    gpsSerial = new Serial4;
}

void serialEvent4()
/* This function is called every time new GPS-data is 
   available at the Serial4 port */
{

}