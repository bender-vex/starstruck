#include <math.h>
#include <main.h>

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
