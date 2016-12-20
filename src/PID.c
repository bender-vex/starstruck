#include <main.h>

/**
 Default PID struct constructor, used for default parameter value
 These specific values represent a smooth curve with no overshoot
 */
const struct PID DEFAULT_PID = { 5, 3, 3 };

/**
 Gets the output of the input passed through the PID controller for the delta time interval
 */
int pid(const int input, long* errorSum, const int prevError, const unsigned long* deltaTime, const int target, const PID pid) {
    // Generate error signal
    int error = target - input;
    *errorSum += error * *deltaTime;
    int dError = (error - prevError) / *deltaTime;

	// Compute PID output
    int output = pid.kp * error + pid.ki * *errorSum + pid.kd * dError;

    return output;
}
