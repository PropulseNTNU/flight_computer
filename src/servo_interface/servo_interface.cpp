#include "servo_interface.h"

Servo servos[NUM_SERVOS];

void init_servo(int servo, int pin) {
    servos[servo].attach(pin);
}

Servo* get_servo(int servo) {
    return &servos[servo];
}