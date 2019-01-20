#include "LED.h"
#include "Arduino.h"

void LEDConfig(int pin){
	pinMode(pin, OUTPUT);
}

void LEDSetMode(int pin, int mode){
	digitalWrite(pin, mode);
}