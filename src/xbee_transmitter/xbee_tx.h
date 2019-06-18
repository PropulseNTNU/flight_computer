#ifndef XBEE_TX_H
#define XBEE_TX_H

#include <stdint.h>

#define RESET_PIN 39 
#define SLEEP_PIN 16 //Don't know what this should be yet
#define TIMER_DELAY 10 //How often to transmit [ms]

#define UART_BAUDRATE 115200
/*
 *  Class for transmitting and receiving data through XBee.
 *
 *  Variables:
 *      num_sens_bytes              Number of bytes in sensor array.
 *      package_number              Incremented for every package that is transmitted.
 *      *sensors                    Pointer to array of sensor data. 
 *
 *  Important methods:
 *      XBee()                      Constructor
 *      transmit();                 Method for transmitting package number, sensor data and flag data. 
 *                                  Remember to update sensor/flag data before transmitting.
 */
class XBee {
  
    uint8_t num_sens_bytes;
    unsigned long timer; 
    uint16_t package_number;
    uint8_t *sensors;     
    
public:
   
    /*
     *   Constructor
     *   Input:
     *       void* sensors           Array of sensor data. Remember to cast to (void*).
     *       uint8_t num_sens        Number of Bytes in sensor array.
     */
    XBee(void* sensors, const uint8_t num_sens);

    /* 
     *  Transmits package number and sensor data.
     *  Format                       <[package_number][sensors]> 
     */
    void transmit(void);

    
    /*
     *   Restart XBee module
     */
    void reset(void);


    /*
     * Put module to sleep.
     */
    void sleep(void);

    /*
     * Wake up module
     */
    void wake_up(void); 
};

#endif
