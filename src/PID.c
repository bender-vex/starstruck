#include "AutoUtils.h"
#include "encoder.h"
#include "PID.h"


PIDHandle* initPID(float kp, float ki, float kd, float target, float error_cap)
{
	PIDHandle* handle = NULL;
	handle = malloc(sizeof(PIDHandle));
	memset(handle, 0, sizeof(PIDHandle));
	handle->kp = kp;
	handle->ki = ki;
	handle->ki = ki;
	handle->error_cap = error_cap;
	handle->target = target;
	handle->integral = 0;
	handle->last_error = 0.0;
	return handle;
}

void freePID(PIDHandle* handle)
{
	free(handle);
}

void setPIDTarget(PIDHandle* handle, float target)
{
	handle->integral = 0;
	handle->target = target;
}

float calculatePID(PIDHandle* handle, float position)
{
	if(handle == NULL) return 0.0;
	float result = 0.0;
	float pid_error = position - handle->target;
	float derivative = 0.0;


	//Integral
	if( handle->ki != 0 )
	{
	// If we are inside controlable window then integrate the error
	if( abs(pid_error) < handle->error_cap || handle->error_cap == 0.0)
	  handle->integral = handle->integral + pid_error;
	else
	  handle->integral = 0;
	}

	// calculate the derivative
	derivative = pid_error - handle->last_error;
	handle->last_error  = pid_error;

	//printf("%5.3f %5.3f %5.3f\n",pid_error, (handle->kp * pid_error), (handle->ki * handle->integral));

	result = (handle->kp * pid_error) + (handle->ki * handle->integral) + (handle->kd * derivative);

	return result;
}

