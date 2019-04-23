#ifndef SERVO_INTERFACE_H
#define SERVO_INTERFACE_H
#include <Servo.h>

#define AIRBRAKES_SERVO_PIN 2
#define DROGUE_SERVO_PIN 3
#define MAIN_SERVO_PIN 4

enum servoEnum {
    AIRBRAKES_SERVO, DROGUE_SERVO, MAIN_SERVO, NUM_SERVOS
};

void init_servo(int servo, int pin, int min_pulse, int max_pulse);

Servo* get_servo(int servo);
#endif
