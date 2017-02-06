#define SIGNUM(num) ((num > 0) - (num < 0))
#define MIN(num1, num2) (num1 < num2 ? num1 : num2)

/**
 * Define constants for motor ports
 */
#define MOTOR_FL 0
#define MOTOR_FR 1
#define MOTOR_BL 2
#define MOTOR_BR 3

/**
 * Use input from joystick to find what the motor outputs should be
 */
void calculateArcadeDrive(const int movement, const int rotation, int *leftSpeed, int *rightSpeed);
