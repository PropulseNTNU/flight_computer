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
enum sensorDataBle { TIME, TROLL, TPITCH, TYAW, 
                 TACCELERATION_X, TACCELERATION_Y, TALTITUDE};


#endif
