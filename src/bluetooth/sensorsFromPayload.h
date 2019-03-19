#ifndef SENSORSFROMPAYLOAD_H
#define SENSORSFROMPAYLOAD_H

/*
 * ID TRANSLATION FROM BLE. 
 * 
 * 'NUMBER_OF_SENSORS' is used to figure out the size 
 * of 'sensorData'. Add/change all the parameter but keep ''NUMBER_OF_SENSORS'
 * at the very end always.   
 * 
 * Currently 13 sensor readings
*/

enum sensorDataBle { TIME, TROLL, TPITCH, TYAW, 
                 TACCELERATION_X, TACCELERATION_Y, TACCELERATION_Z,
                 TCOMPASS_X, TCOMPASS_Y, TCOMPASS_Z ,
                 TEMPERATURES , THUMIDITY, TALTITUDE, NUMBER_OF_SENSORS};



#endif
