#ifndef _GYRO_H_
#define _GYRO_H_

#include "PID.h"

/**
 Build the thread the gyro reads from
 */
TaskHandle startGyro();

/**
 Close the thread the gyro reads from
 */
void stopGyro(TaskHandle taskHandle);

/**
 Resets the gyro sensor, effectively setting the current heading to zero
 */
void resetGyro();

/**
 Gets the current heading of the gyro in degrees
 */
void getHeading();


#endif