#include "servo_interface.h"

Servo servos[NUM_SERVOS];

void init_servo(int servo, int pin, int min_pulse, int max_pulse) {
    servos[servo].attach(pin, min_pulse, max_pulse);
}

Servo* get_servo(int servo) {
    return &servos[servo];
}
