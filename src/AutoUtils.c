#include "AutoUtils.h"

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
}

void freePID(PIDHandle* handle)
{
	free(handle);
}


void placeHolder()
{
	printf("Place Holder\n");
}



