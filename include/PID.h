/**
 Proportional integral derivative controller property structure
 Describes the PID curve used to perform dampening caluclations
 */
struct PID {
    int kp;
    int ki;
    int kd;
};

/**
 Default PID struct constructor, used for default parameter value
 These specific values represent a smooth curve with no overshoot
 */
const struct PID DEFAULT_PID = { 5, 3, 3 };

/**
 Gets the output of the input passed through the PID controller for the delta time interval
 */
int pid(int input, int *errorSum, unsigned long deltaTime, int target = 0, PID pid = DEFAULT_PID) {
    // Generate error signal
	int error = target - input;
    *errorSum += error;
	int dError = error - *errorSum;

	// Compute PID output
	int output = pid.kp * error + pid.ki * *errorSum + pid.kd * dError;

    return output;
}
