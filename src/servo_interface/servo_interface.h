#include <Servo.h>

#define AIRBRAKES_SERVO_PIN 9

enum servoEnum {
    AIRBRAKES_SERVO, NUM_SERVOS
};

void init_servo(int servo, int pin);

Servo* get_servo(int servo);