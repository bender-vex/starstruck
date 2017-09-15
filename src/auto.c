/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/// The main auto
void autoPrimary()
{
	clawPower(-25);
	delay(500);
	clawPower(0);
	setArmTarget(120);
	moveY(1700);
	delay(4000);
	clawPower(-64);
	delay(500);
	clawPower(0);
	moveX(1000);
	delay(1500);
	setAutoDriveMode(NONE);
}

/// Sweep stars off fence
void autoFenceSweep()
{
	setHeading(180);
	delay(800);
	moveX(500);
	delay(1000);
	moveY(-1300);
	delay(1000);
	clawPower(-20);
	delay(500);
	clawPower(0);
	setArmTarget(250);
	delay(1000);
	moveX(1500);
	delay(1500);
}


 /*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous()
{
	autoPrimary();
}
