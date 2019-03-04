/* Simple the wrapper for the TinyGPS++ library with an
implementation of serialEvent4() for reading
raw NMEA data from a MTK3339 GPS module. It is intended
to be used in the flight computer of the Sleipner rocket
created by Propulse NTNU. 
- Ole Bjørn Eithun Pedersen 2019.

This code is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "TinyGPS++.h"

#ifndef BUFFER_SENTENCES
#define BUFFER_SENTENCES 4
#endif

#ifndef GPS_BAUDRATE
#define GPS_BAUDRATE 9600
#endif

#ifndef GPS_MAX_WAIT_MILLI
#define GPS_MAX_WAIT_MILLI 200
#endif

/* The GPS class is implemented with the singelton design pattern. It
guarantees that only one instance of the class can exist at any given
time. */
class GPS : public TinyGPSPlus 
{
public:
    static GPS& getInstance(); // Get pointer to the only instance
    
    void sendCommand(const char *command); // Send command

    // Set functions
    void setUpdateRate(unsigned int updateRate);
    void stop(); // Stops the automatic updating of the GPS
    void start(); // Starts the automatic updating if turned off
    // Get functions
    double getAltitude(); // Returns alltitude in meters
    double getLatitude();
    double getLongitude();
    double getSpeed(); // Returns speed in m/s

    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();

    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();

private:
    GPS() {}
    GPS(GPS const&);
    void operator=(GPS const&);
    char* nmeaBuffer[]; // Buffer for NMEA sentences
    unsigned int bufferSentences; // Number of NMEA sentences to store in buffer2

    HardwareSerial* gpsSerial; /* Serial object for uart communication with gps.
                           Serial4 must be used, pins Rx->31 Tx->32 on the Teensy3.6,
                           is used on the flight computer. */
    unsigned int baudrate; // Baudrate for GPS
};
