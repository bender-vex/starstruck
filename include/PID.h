#ifndef PID_H_
#define PID_H_

#include <math.h>
#include <API.h>
#include <string.h>
#include <drive.h>

typedef struct
{
	float kp; // P constant
	float ki; // I constant
	float kd; // D constant
	float target; //The value we want to reach
	float last_error;
	float error_cap;
	float integral;
} PIDHandle;

PIDHandle* initPID(float kp, float ki, float kd, float target, float error_cap);
void setPIDTarget(PIDHandle* handle, float target);
void freePID(PIDHandle* handle);
float calculatePID(PIDHandle* handle, float position);



#endif
