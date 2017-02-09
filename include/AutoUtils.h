#include <math.h>
#include <api.h>
#include <string.h>

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


char runHeadingThread;
TaskHandle heading_thread;
void initHeadingThread();

PIDHandle* initPID(float kp, float ki, float kd, float target, float error_cap);
void setPIDTarget(PIDHandle* handle, float target);
void freePID(PIDHandle* handle);
float calculatePID(PIDHandle* handle, float position);


void turnBase(short power);
void moveBase(short x, short y, short r);

