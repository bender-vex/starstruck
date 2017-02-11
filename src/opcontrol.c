/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl()
{
	
	initHeadingThread();
	delay(20);
	setAutoDriveMode(X_ROTATION);
	delay(200);
	x_pid = initPID(0.5,0.0,0.0,0,0);
	setPIDTarget(x_pid, 400.0);
	delay(1500);
	setPIDTarget(x_pid, 0.0);
	/*
	delay(2000);
	setHeading(90);
	delay(2000);
	setHeading(180);
	delay(2000);
	setHeading(0);
	delay(2000);
	setAutoDriveMode(X_ROTATION);
	delay(2000);
	setAutoDriveMode(ROTATION_ONLY);
	delay(100);
	setHeading(180);
	delay(1500);
	setAutoDriveMode(X_ROTATION);
	delay(2000);
	setAutoDriveMode(NONE);
	*/
	
	
	
	while (1) 
	{
		//setAutoDriveMode(X_ROTATION);
		//printf("%6d\n",ultrasonicGet(sonic));
		//moveBase(joystickGetAnalog(1,4),joystickGetAnalog(1,3),joystickGetAnalog(1,1));
		//moveBase(0,calculatePID(upid,ultrasonicGet(sonic)),0);
		//moveBase(0,0,60);
		delay(20);
	}
}
