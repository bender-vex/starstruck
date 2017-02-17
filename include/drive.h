#ifndef DRIVE_H_
#define DRIVE_H_

#define SIGNUM(num) ((num > 0) - (num < 0))
#define MIN(num1, num2) (num1 < num2 ? num1 : num2)

/**
 * Define constants for motor ports
 */
#define MOTOR_FRONT_LEFT 10
#define MOTOR_FRONT_RIGHT 9
#define MOTOR_BACK_LEFT 2
#define MOTOR_BACK_RIGHT 1

void turnBase(short power);
void moveBase(short x, short y, short r);

#endif
