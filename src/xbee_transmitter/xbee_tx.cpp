#include "xbee_tx.h"
#include <Arduino.h>


XBee::XBee(void* data1, const uint8_t size_data1, void* data2, const uint8_t size_data2) 
        : timer(millis()), package_number(0),size_data1(size_data1), size_data2(size_data2), data1((uint8_t*)data1), data2((uint8_t*)data2) {
         
          //Activating serial communication
          Serial5.begin(UART_BAUDRATE);
          Serial5.setTimeout(25);

          //Resetting module
          reset();

          //Setting up sleep pin
          //pinMode(SLEEP_PIN, OUTPUT);
          //digitalWrite(SLEEP_PIN, LOW);     
          Serial.println("XBee initialized");
    }


void XBee::reset(void) {
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(RESET_PIN, LOW);
    delay(1);
    pinMode(RESET_PIN, INPUT);
}

void XBee::transmit(void) {
    if(millis()-timer > TIMER_DELAY) {
        Serial5.write('<');
        Serial5.write((uint8_t*)&(++package_number), sizeof(package_number));
        Serial5.write(data1, 2*8);
        Serial5.write(data2, 0);
        Serial5.write('>');
        timer = millis();
        Serial.print("DATA 0: ");
        Serial.println(data1[0]);
    }
}


void XBee::sleep(void) {
    digitalWrite(SLEEP_PIN, HIGH);
}

void XBee::wake_up(void) {
    digitalWrite(SLEEP_PIN, LOW);
}



