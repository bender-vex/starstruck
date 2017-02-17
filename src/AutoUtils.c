#include "AutoUtils.h"
#include "encoder.h"


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


void initAutoGlobals()
{
	gyro_pid = NULL;
	x_pid = NULL;
	y_pid = NULL;
	arm_pid = NULL;
	runHeadingThread = 0;
	runArmThread = 0;
	drive_mode = NONE;
	e_left = encoderInit(1,2,1);
	e_right = encoderInit(3,4,1);//Flip to 1 for y
	e_arm = encoderInit(5,6,1);
	arm_pid = initPID(2.5,0.12,0.0,0,10);//TODO configure this
	y_pid = initPID(0.5,0.5,0.0,0.0,0.0);
	x_pid = initPID(0.5,0.0,0.0,0.0,0.0);
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

void clawPower(int power)
{
	motorSet(CLAW_MOTOR, power);
}

void setHeading(int angle)
{
	if(gyro_pid != NULL)
	{
		setPIDTarget(gyro_pid, angle);
	}
}

void driveThread(void* param)
{

	gyro_pid = initPID(2.5,0.12,.5,0,10);
	setPIDTarget(gyro_pid,0.0);
	Gyro gyro;
	gyro = gyroInit( 1, 0 );

	//drive_mode = ROTATION_ONLY;

	//TODO Configure x and y
	//TODO add sweet zone algorithm for x and y
	//TODO get encoder code working
	// = initPID(0.5,0.0,0.0,0,0);
	float m_x = 0;
	float c_x = 0;
	while(runHeadingThread)
	{
		delay(20);
		//printf("lol: %d\n",drive_mode);
		printf("%6d %6d\n",encoderGet(e_left), encoderGet(e_right));
		switch(drive_mode)
		{
			case NONE: break;
			case ROTATION_ONLY:
			{
				moveBase(0,0,calculatePID(gyro_pid,gyroGet(gyro)));
			}break;
			case X_ROTATION:
			{
				c_x = clampF(calculatePID(gyro_pid,gyroGet(gyro)), -60,60);
				m_x = calculatePID(x_pid, (encoderGet(e_left) + encoderGet(e_right))/2);
				m_x = clampF(m_x,-60,60);
				int val = (int)m_x * -1;
				//printf("r= %f\n",m_x);
				moveBase(val,0,c_x);
			}break;
			case Y_ROTATION:
			{
				c_x = clampF(calculatePID(gyro_pid,gyroGet(gyro)), -60,60);
				m_x = calculatePID(y_pid, (encoderGet(e_left) + encoderGet(e_right))/2);
				m_x = clampF(m_x,-60,60);
				int val = (int)m_x * -1;
				//printf("r= %f\n",m_x);
				moveBase(val,0,c_x);
			}break;
			case X_ONLY:
			{

			}break;
			case Y_ONLY:
			{

			}break;
		}


		//moveBase(0,-calculatePID(upid,uvalue),calculatePID(gyro_pid,gyroGet(gyro)));
	}
	freePID(gyro_pid);
	gyro_pid = NULL;
	freePID(x_pid);
	x_pid = NULL;
	freePID(y_pid);
	y_pid = NULL;
}

void armPower(int power)
{
	motorSet(ARM_MOTOR_L_B, -power);
	motorSet(ARM_MOTOR_L_T, power);
	motorSet(ARM_MOTOR_R_B, power);
	motorSet(ARM_MOTOR_R_T, -power);
}

void setArmTarget(int target)
{
	if(arm_pid != NULL)
	{
		arm_pid->target = target;
	}
}

void armThread(void* param)
{

	int power = 0;
	while(runArmThread)
	{
		power = -calculatePID(arm_pid, encoderGet(e_arm));
		armPower(power);
		delay(20);
	}
	freePID(arm_pid);
}

void stopHeadingThread()
{
	runHeadingThread = 0;
}

void initHeadingThread()
{
	runHeadingThread = 1;
	taskCreate(driveThread, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void initArmThread()
{
	runArmThread = 1;
	taskCreate(armThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void setAutoDriveMode(AutoDriveMode adm)
{
	drive_mode = adm;
}

void pickUpMacroThread()
{
	delay(250);
	setArmTarget(-145);
	delay(1500);
	clawPower(-127);
	delay(500);
	clawPower(-50);
	setArmTarget(0);
}

void tossMacroThread()
{
	setArmTarget(250);
	delay(1500);
	setArmTarget(00);
	delay(375);
	clawPower(127);
	delay(200);
	clawPower(0);
}

void tossMacro()
{
	//TODO Make less stupid and add safety (Cant run more than 1 and cancel mode)
	taskCreate(tossMacroThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void pickUpMacro()
{
	//TODO Make less stupid and add safety (Cant run more than 1 and cancel mode)
	taskCreate(pickUpMacroThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}


float clampF(float value, float min, float max)
{
	if(value < min)
	{
		return min;
	}
	else if(value > max)
	{
		return max;
	}
	return value;
}

int clampI(int value, int min, int max)
{
	if(value < min)
	{
		return min;
	}
	else if(value > max)
	{
		return max;
	}
	return value;
}

void setXTarget(int target)
{
	//x_pid = initPID(0.2,0.12,0.2,0,0);
	if(x_pid != NULL)
	{
		//setAutoDriveMode(ROTATION_ONLY);
		//int current = x_pid->target;
		//setPIDTarget(x_pid, 400.0);
		//x_pid->target += target;
	}
}
