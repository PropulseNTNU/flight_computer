#ifndef SENSORSFROMPAYLOAD_H
#define SENSORSFROMPAYLOAD_H

/*
 * ID TRANSLATION FROM BLE. 
 * 
 * 'NUMBER_OF_SENSORS' is used to figure out the size 
 * of 'sensorData'. Add/change all the parameter but keep ''NUMBER_OF_SENSORS'
 * at the very end always.   
 * 
 * Currently 15 sensor readings
*/

enum allSensorDataBle { ATIME, AROLL, APITCH, AYAW, 
                 AACCELERATION_X, AACCELERATION_Y, AACCELERATION_Z,
                 ACOMPASS_X, ACOMPASS_Y, ACOMPASS_Z,
		 ATEMPERATURES , AHUMIDITY, AALTITUDE, APRESSURE, AGAS, 
		 ATEMP_ACCUR_SENS}; 

enum sensorDataBle { TIME, TROLL, TPITCH, TYAW, 
                 TACCELERATION_X, TALTITUDE, NUMBER_OF_SENSORS};


#endif
