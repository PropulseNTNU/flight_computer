#ifndef AIRBRAKES_KALMAN_H
#define AIRBRAKES_KALMAN_H

void kalman(float* estimate, float  altitude, float acceleration, float dt, float reference_v);

#endif
