#ifndef _GYRO_H_
#define _GYRO_H_

#include "API.h"

extern const int GYRO_CHANNEL;
extern const int GYRO_MULTIPLIER;
extern const unsigned int FIXED_DELTA_TIME;

/**
 * Starts the gyro sensor and returns a taskhandle for the thread it's read on
 */
TaskHandle startGyro();

/**
 * Stop and delete the gyro reading thread, reset global variables
 */
void stopGyro(TaskHandle taskHandle);

/**
 * Thread to read the gyro from
 */
void readGyro();

/**
 * Must be called after startGyro() has been called, deltaTime is in milliseconds
 */
void getHeading();

#endif
