#include "AutoUtils.h"

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
	//e_back = encoderInit(7, 8, 1);
	arm_pid = initPID(2.1,0.12,0.0,0,5);
	y_pid = initPID(0.5,0.0,0.0,0.0,10.0);
	x_pid = initPID(0.5,0.0,0.0,0.0,10.0);
	arm_macro_mutex = false;
}

void turnBase(short power)
{
	motorSet(MOTOR_BACK_RIGHT, power);
	motorSet(MOTOR_BACK_LEFT, power);
	motorSet(MOTOR_FRONT_RIGHT, power);
	motorSet(MOTOR_FRONT_LEFT, -power);
}

void moveBase(short x, short y, short r)
{
	motorSet(MOTOR_BACK_RIGHT, -(y - r + x)); // Back Right
	motorSet(MOTOR_BACK_LEFT, y + r - x);     // Back Left
	motorSet(MOTOR_FRONT_RIGHT, -y + r + x);    // Front Right
	motorSet(MOTOR_FRONT_LEFT, -(y + r + x)); // Front Left
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
	float movement_x = 0, movement_y = 0, rotation = 0;
	while(runHeadingThread)
	{
		delay(20);
		//printf("lol: %d\n",drive_mode);
		//printf("Left: %6d Right: %6d Back: %6d\n",encoderGet(e_left), encoderGet(e_right), encoderGet(e_back));
		switch(drive_mode)
		{
			case NONE: break;
			case ROTATION_ONLY:
			{
				moveBase(0,0,calculatePID(gyro_pid,gyroGet(gyro)));
			}break;
			case X_ROTATION:
			{
				rotation = clampF(calculatePID(gyro_pid,gyroGet(gyro)), -60,60);// value is now between -60 and 60
				movement_x = calculatePID(x_pid, (encoderGet(e_left) + encoderGet(e_right))/2);// left and right encoders are averaged
				movement_x = clampF(movement_x,-60,60);
				int val = (int)movement_x * -1;
				moveBase(val,0,rotation);
			}break;
			case Y_ROTATION:
			{
				rotation = clampF(calculatePID(gyro_pid,gyroGet(gyro)), -60,60);
				movement_y = calculatePID(y_pid, ((encoderGet(e_left) * -1) + (encoderGet(e_right))/2));// average left and back encoders
				movement_y = clampF(movement_y,-60,60);
				//printf("Value: %d\n",encoderGet(e_left));
				int val = (int)movement_y * -1;
				moveBase(0,val,rotation);
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

void resetEncoders()
{
	encoderReset(e_right);
	encoderReset(e_left);
}

void armPower(int power)
{
	motorSet(ARM_MOTOR_TOP, -power);
	motorSet(ARM_MOTOR_BOTTOM, power);
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
		if(arm_pid->target == -999)
		{
			power = 0;
		}
		else
		{
			power = -calculatePID(arm_pid, encoderGet(e_arm));
		}
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

void pickUpUpCubeMacroThread()
{
	arm_macro_mutex = true;
	clawPower(-127);
	delay(750);
	clawPower(-110);
	setArmTarget(-999);
	arm_macro_mutex = false;
	return;
}

void pickUpDownCubeMacroThread()
{
	arm_macro_mutex = true;
	delay(500);
	setArmTarget(CLAW_GROUND_CUBE);
	arm_macro_mutex = false;
	return;
}

void pickUpDownMacroThread()
{
	arm_macro_mutex = true;
	delay(500);
	setArmTarget(CLAW_GROUND);
}

void pickUpUpMacroThread()
{
	clawPower(-127);
	delay(750);
	clawPower(-55);
	setArmTarget(-999);
	arm_macro_mutex = false;
}

void tossMacroThread()
{
	arm_macro_mutex = true;
	setArmTarget(CLAW_BACK);
	delay(500 + 750);
	setArmTarget(60);
	clawPower(-127);
	waitEncoderLess(CLAW_RELEASE_BASIC,e_arm);
	clawPower(127);
	delay(600);
	clawPower(-127);
	delay(200);
	clawPower(0);
	arm_macro_mutex = false;
}



void tossMacro()
{
	//TODO Make less stupid and add safety (Cant run more than 1 and cancel mode)
	if(arm_macro_mutex == false)
	{
		taskCreate(tossMacroThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	}
}

void pickUpDownMacro()
{
	//TODO Make less stupid and add safety (Cant run more than 1 and cancel mode)
	if(arm_macro_mutex == false)
	{
		taskCreate(pickUpDownMacroThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	}
}

void pickUpUpMacro()
{
	//TODO Make less stupid and add safety (Cant run more than 1 and cancel mode)
	if(arm_macro_mutex == false)
	{
		taskCreate(pickUpUpMacroThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	}
}

void pickUpUpCubeMacro()
{
	//TODO Make less stupid and add safety (Cant run more than 1 and cancel mode)
	if(arm_macro_mutex == false)
	{
		taskCreate(pickUpUpCubeMacroThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	}
}

void pickUpDownCubeMacro()
{
	//TODO Make less stupid and add safety (Cant run more than 1 and cancel mode)
	if(arm_macro_mutex == false)
	{
		taskCreate(pickUpDownCubeMacroThread,  TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	}
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

void waitEncoderGreater(int value, Encoder encoder)
{
	while( encoderGet(encoder) < value) delay(50);
}

void waitEncoderLess(int value, Encoder encoder)
{
	while( encoderGet(encoder) > value) delay(50);
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

void moveY(int distance)
{
	setAutoDriveMode(Y_ROTATION);
	resetEncoders();
	setPIDTarget(y_pid, distance);
}

void moveX(int distance)
{
	setAutoDriveMode(X_ROTATION);
	resetEncoders();
	setPIDTarget(x_pid, distance);
}
