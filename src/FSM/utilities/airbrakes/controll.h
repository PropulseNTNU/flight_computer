#ifndef AIRBRAKES_CONTROLL_H
#define AIRBRAKES_CONTROLL_H
#include <BasicLinearAlgebra.h>

using namespace BLA;

//structs
typedef struct Parameters_t {
  float kpp;
  float kpi;
  float kpd;
}Parameters;


float controller(float* error, Parameters* parameters, float* riemann_sum, float dt);
float integrate(float prev_sum, float value, float step);


#endif
