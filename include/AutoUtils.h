#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct
{
	float kp; // P constant
	float ki; // I constant
	float kd; // D constant
	float target; //The value we want to reach
	float last_error;
	float error_cap;
} PIDHandle;

PIDHandle* initPID(float kp, float ki, float kd = 0.0f, float error_cap = 0.0f);
void freePID(PIDHandle* handle);


void placeHolder();



