#ifndef _PID_H_
#define _PID_H_

/**
 Proportional integral derivative controller property structure
 Describes the PID curve used to perform dampening caluclations
 */
typedef struct PID {
    int kp;
    int ki;
    int kd;
} PID;

/**
 Default PID struct constructor, used for default parameter value
 These specific values represent a smooth curve with no overshoot
 */
extern const PID DEFAULT_PID;

/**
 Gets the output of the input passed through the PID controller for the delta time interval
 */
int pid(const int input, long* errorSum, const int prevError, const unsigned long* deltaTime, const int target, const PID pid);

#endif