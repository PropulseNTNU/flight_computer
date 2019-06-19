#include "controll.h"
#include "Arduino.h"

#include <math.h>

//varibles for testing
float flap_width=0.1106; // the with of the air brake flap in meters. This is only for testing, and will not be used during flight
float max_extention= 0.02;//0.02; //the max length of the air brake flaps in meters. This is only for testing, and will not be used during flight
float flaps = 3;

float getAirbrakesArea() {
  return flaps * flap_width * max_extention;
}

float integrate(float prev_sum, float value, float step){
  return prev_sum + (value * step);
}

float pros_to_deg(float prosent){
  return asin(prosent/100.0) * 180.0/PI;
}

float controller(float* error, ControlParameters* parameters, float* riemann_sum, float dt){ //PI-controller
  // add a lower and upper bound to prevernt overflow
  if(integrate(*riemann_sum, *error, dt) <= 40 && integrate(*riemann_sum, *error, dt) > -40){
    *riemann_sum = integrate(*riemann_sum, *error, dt); //integrates error
  }

  float prosent = (parameters->kpp*(*error)) + (parameters->kpi*(*riemann_sum));
  if (prosent > 86.6){
    return 60;
  }
  else if(prosent<0.0){
    return 0;
  }
  else {
    return pros_to_deg(prosent);
  }
}


//functions for testing
float test_calculate_area(float u){
  return getAirbrakesArea()*sin((u * 71) / 4068.0); // sin takes radians as input
}