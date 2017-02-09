#define SIGNUM(num) ((num > 0) - (num < 0))
#define MIN(num1, num2) (num1 < num2 ? num1 : num2)

/**
 * Define constants for motor ports
 */
#define MOTOR_FRONT_LEFT 1
#define MOTOR_FRONT_RIGHT 2
#define MOTOR_BACK_LEFT 9
#define MOTOR_BACK_RIGHT 10

/**
 * Use input from joystick to find what the motor outputs should be
 */
void calculateArcadeDrive(const int movement, const int rotation, int *leftSpeed, int *rightSpeed);

/**
 * Control the robot's drivetrain with joysticks. This function should be called frequently in teleop.
 */
void arcadeDrive();

/**
 * Set the speed of the motors on the left side of the drivetrain.
 */
void setLeftMotors(const int speed);

/**
 * Set the speed of the motors on the right side of the drivetrain.
 */
void setRightMotors(const int speed);
