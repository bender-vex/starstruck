#include <main.h>

/**
 Default PID struct constructor, used for default parameter value
 These specific values represent a smooth curve with no overshoot
 */
const struct PID DEFAULT_PID = { 5, 3, 3 };

/**
 Gets the output of the input passed through the PID controller for the delta time interval
 */
float pid(float input, double *errorSum, float prevError, const unsigned long * const deltaTime, float target, const PID pid) {
    // Generate error signal
	float error = target - input;
    *errorSum += error * *deltaTime;
	float dError = (error - prevError) / *deltaTime;

	// Compute PID output
	float output = pid.kp * error + pid.ki * *errorSum + pid.kd * dError;

    return output;
}
