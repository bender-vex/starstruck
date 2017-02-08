#include <math.h>
#include <main.h>

/**
 * Use input from joystick to find what the motor outputs should be
 */
void calculateArcadeDrive(const int movement, const int rotation, int *leftSpeed, int *rightSpeed){
	*leftSpeed = movement + rotation;
	*rightSpeed = movement - rotation;
	
	// restrict motor output values to -127 to 127
	*leftSpeed = SIGNUM(*leftSpeed) * MIN(abs(*leftSpeed), 127);
	*rightSpeed = SIGNUM(*rightSpeed) * MIN(abs(*rightSpeed), 127);
}

void arcadeDrive(){
	int *leftSpeed = malloc(sizeof(int));
	int *rightSpeed = malloc(sizeof(int));
	calculateArcadeDrive(joystickGetAnalog(1, 3), joystickGetAnalog(1, 1), leftSpeed, rightSpeed);
	setLeftMotors(*leftSpeed);
	setRightMotors(*rightSpeed);
}

void setLeftMotors(const int speed){
	motorSet(MOTOR_FRONT_LEFT, speed);
	motorSet(MOTOR_BACK_LEFT, speed);
}

void setRightMotors(const int speed){
	// right side motors are inverted
	motorSet(MOTOR_FRONT_RIGHT, -speed);
	motorSet(MOTOR_BACK_RIGHT, -speed);
}
