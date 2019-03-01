/* Simple the wrapper for the TinyGPS++ library with an
implementation of the serialEvent4() for reading
raw NMEA data from a MTK3339 GPS module. It is intended
to be used in the flight computer of the Sleipner rocket
created by Propulse NTNU. 

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

#ifndef GPS_BAUDRATE
#define GPS_BAUDRATE 9600
#endif

class GPS : public TinyGPSPlus 
{
public:
    GPS(); // Constructor
    
    // Set functions
    void setUpdateRate(unsigned int updateRate);
    void stop(); // Stops the automatic updating of the GPS

    // Get functions
    double getAlltitude(); // Returns alltitude in meters
    double getLatitude();
    double getLongitude();
    double getSpeed(); // Returns speed in m/s

    uint16_t getYear();
    unint8_t getMonth();
    uint8_t getDay();

private:
    char* buffer[]; // Buffer for NMEA sentences
    unsignend int bufferSentences; // Number of NMEA sentences to store in buffer

    Serial4* gpsSerial; /* Serial object for uart communication with gps.
                           Serial4, which corresponds to pins Rx->31 Tx->32
                           on the Teensy3.6, is used on the flight computer. */
    unsignend int baudrate; // Baudrate for GPS
};