#include "main.h"
#include "PID.h"

/**
 Default PID struct constructor, used for default parameter value
 These specific values represent a smooth curve with no overshoot
 */
const struct PID DEFAULT_PID = { 5, 3, 3 };

/**
 Gets the output of the input passed through the PID controller for the delta time interval
 */
int pid(int input, int *errorSum, const unsigned long * const deltaTime, int target, PID pid) {
    // Generate error signal
	int error = target - input;
    *errorSum += error;
	int dError = error - *errorSum;

	// Compute PID output
	int output = pid.kp * error + pid.ki * *errorSum + pid.kd * dError;

    return output;
}
