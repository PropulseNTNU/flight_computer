
#include "interpolation.h"
#include "Arduino.h"

// Lookuptable based on optimal path calculated by the simulation. It will be represented as an array off height(index) -> velocity pairs
const float reference_velocity[5] = {100,75,60,55,52};

float getReferenceVelocity(float height){ //Linear interpolation between heights
  unsigned int x0 = floor(height);
  unsigned int x1 = x0 + 1;
  float y0 = reference_velocity[x0];
  float y1 = reference_velocity[x1];
  return ((y0 * (x1 - height)) + (y1 * (height - x0 ))) / (x1 - x0);
}
