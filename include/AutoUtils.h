#ifndef AUTOUTILS_H_   /* Include guard */
#define AUTOUTILS_H_

#include <math.h>
#include <api.h>
#include <string.h>
#include <drive.h>

#define ARM_MOTOR_L_r_1 3
#define ARM_MOTOR_L_2 4
#define ARM_MOTOR_L_3 5
#define ARM_MOTOR_R_2 7
#define ARM_MOTOR_R_3 8


typedef enum {NONE = 0, ROTATION_ONLY = 1, X_ROTATION = 2, Y_ROTATION, X_ONLY, Y_ONLY} AutoDriveMode;

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
char runArmThread;
TaskHandle heading_thread;
void initHeadingThread();
void initAutoGlobals();
void setAutoDriveMode(AutoDriveMode adm);
void setHeading(int angle);
void setXTarget(int target);

PIDHandle* initPID(float kp, float ki, float kd, float target, float error_cap);
void setPIDTarget(PIDHandle* handle, float target);
void freePID(PIDHandle* handle);
float calculatePID(PIDHandle* handle, float position);


void turnBase(short power);
void moveBase(short x, short y, short r);


float clampF(float value, float min, float max);
int clampI(int value, int min, int max);


//Globals
AutoDriveMode drive_mode;
PIDHandle* gyro_pid;
PIDHandle* x_pid;
PIDHandle* y_pid;
PIDHandle* arm_pid;

Encoder e_right;
Encoder e_left;
#endif
