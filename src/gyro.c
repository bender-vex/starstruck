#include "gyro.h"

const int GYRO_CHANNEL = 1;
const int GYRO_MULTIPLIER = 1;
const unsigned int FIXED_DELTA_TIME = 20;
int heading = 0;

/**
 * Starts the gyro sensor and returns a taskhandle for the thread it's read on
 */
TaskHandle startGyro() {
	// Calibrate and start the gyro sensor, set a task to read the sensor from
	gyroInit(GYRO_CHANNEL, 1);
	return taskCreate(readGyro, 1, NULL, 1);
}

/**
 * Stop and delete the gyro reading thread, reset global variables
 */
void stopGyro(TaskHandle taskHandle) {
	// Destroy the task passed in
	taskDelete(taskHandle);
	// Set the current heading to 0
	heading = 0;
}

/**
 * Thread to read the gyro from
 */
void readGyro() {
	heading = 0;
	while (1) {
		getHeading(FIXED_DELTA_TIME);
		delay(FIXED_DELTA_TIME);
	}
}


/**
 * Must be called after startGyro() has been called, deltaTime is in milliseconds
 */
void getHeading(unsigned int deltaTime) {
	// Read the calibrated values and account for sensor drift
	int rot = analogReadCalibratedHR(GYRO_CHANNEL);
	
	heading += rot * deltaTime / 1000;
}