#include "gps.h"
#include "nmeacommands.h"

GPS& GPS::getInstance() 
{
    static GPS instance;
    instance.gpsSerial = &Serial4;
    instance.baudrate = GPS_BAUDRATE;
    instance.gpsSerial->begin(instance.baudrate);
    return instance;
}

void GPS::sendCommand(const char *command)
{
    if (!*gpsSerial)
        return;
    gpsSerial->println(command);
}

void GPS::stop() 
{
    gpsSerial->end();
}

void GPS::start()
{
    if (!*gpsSerial)
        gpsSerial->begin(baudrate);
}

void GPS::setUpdateRate(unsigned int updateRate)
{
    if (!*gpsSerial)
        return;
    switch (updateRate) {
        case 1:
            gpsSerial->println(PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ);
            break;
        case 2:
            gpsSerial->println(PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ);
            break;
        case 10:
            gpsSerial->println(PMTK_SET_NMEA_UPDATE_1HZ);
            break;
        case 20:
            gpsSerial->println(PMTK_SET_NMEA_UPDATE_2HZ);
            break;
        case 50:
            gpsSerial->println(PMTK_SET_NMEA_UPDATE_5HZ);
            break;
        case 100:
            gpsSerial->println(PMTK_SET_NMEA_UPDATE_10HZ);
        default:
            break;
    }
    
}

double GPS::getAltitude() 
{
    return altitude.meters();
}

double GPS::getLatitude() 
{
    return location.lat();
}

double GPS::getLongitude() 
{
    return location.lng();
}

double GPS::getSpeed() 
{
    return speed.mps();
}

uint16_t GPS::getYear() 
{
    return date.year();
}

uint8_t GPS::getMonth() 
{
    return date.month();
}

uint8_t GPS::getDay() 
{
    return date.day();
}

uint8_t GPS::getHour()
{
    return time.hour();
}

uint8_t GPS::getMinute() 
{
    return time.minute();
}

uint8_t GPS::getSecond() 
{
    return time.second();
}
