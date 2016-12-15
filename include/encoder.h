#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <main.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

/**
 Get total distance traveled in meters since last reset
 The diameter param should be in units of meters
 */
float getDistance(Encoder encoder, float diameter);

#endif
