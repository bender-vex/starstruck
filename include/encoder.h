#ifndef _ENCODER_H_
#define _ENCODER_H_

#define ENCODER_BR 0
#define ENCODER_BL 1
#define IME_COUNT 2

#include "API.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif

/**
 Get total distance traveled in meters since last reset
 The diameter param should be in units of meters
 */
float getDistance(Encoder encoder, float diameter);

#endif
