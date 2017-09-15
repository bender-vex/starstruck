/** \file AutoUtils.h
 * \brief Jesus Christ
 */

#ifndef AUTOUTILS_H_
#define AUTOUTILS_H_

#include <math.h>
#include <API.h>
#include <drive.h>
#include "PID.h"

#define ARM_MOTOR_BOTTOM 3
#define ARM_MOTOR_TOP 4
#define CLAW_MOTOR 8

#define CLAW_REST 180
#define CLAW_GROUND -30
#define CLAW_GROUND_CUBE 375
#define CLAW_VERT 210
#define CLAW_BACK 320
#define CLAW_RELEASE_BASIC 240


typedef enum {NONE = 0, ROTATION_ONLY = 1, X_ROTATION = 2, Y_ROTATION, X_ONLY, Y_ONLY} AutoDriveMode;



char runHeadingThread;
char runArmThread;
TaskHandle heading_thread;

/**
 * Initialize the thread for the gyro
 */
void initHeadingThread();

/**
 * Initialize all the global variables.
 * Should only be called once.
 */
void initAutoGlobals();

/**
 * Change the autonomous drive mode
 * \param adm the AutoDriveMode enumeration
 */
void setAutoDriveMode(AutoDriveMode adm);

/**
 * Set the target for the gyro
 * \param angle target angle in degrees
 */
void setHeading(int angle);

/**
 * Initialize the thread for the arm.
 * Should only be called once.
 */
void initArmThread();

/**
 * Set PID target for drivetrain on the x-axis.
 * \param target encoder tick target
 */
void setXTarget(int target);

/**
 * Reset the value for the encoders
 */
void resetEncoders();




//Easy move stuff

/**
 * Use PID to move on the x-axis
 * \param distance the distance to move
 */
void moveX(int distance);

/**
 * Use PID to move on the y-axis
 * \param distance the distance to move
 */
void moveY(int distance);




/**
 * Push all the stars on a fence to the other side of the field
 */
void clearFence();

/**
 * Push a star to the other side of the field
 */
void pushFenceStar();




/**
 * Rotate the drivetrain
 * \param power speed to turn with
 */
void turnBase(short power);

/**
 * Move the robot using the drivetrain
 * \param x movement value on the x-axis
 * \param y movement value on the y-axis
 * \param r rotation value
 */
void moveBase(short x, short y, short r);

/**
 * Control the speed of the arm motors
 * \param power motor speed
 */
void armPower(int power);

/**
 * Change the speed value of the claw motors
 * \param power motor speed value
 */
void clawPower(int power);

/**
 * Change the PID target for the arm
 * \param target new PID target
 */
void setArmTarget(int target);



/**
 * The part of the cube pick-up macro where the claw moves upward after picking up a cube
 */
void pickUpUpCubeMacro();

/**
 * The part of the cube pickup macro where the claw moves downward
 */
void pickUpDownCubeMacro();

/**
 * The first part of the  pick up macro where the claw moves downward
 */
void pickUpDownMacro();

/**
 * The part of the pick up macro where the claw moves upward after grabbing a star
 */
void pickUpUpMacro();

/**
 * Toss a star or cube
 */
void tossMacro();

bool arm_macro_mutex;


//Utilities

/**
 * Normalize the value of a float
 * \param value the value to be clamped
 * \param min the minimum valid value
 * \param max the maximum valid value
 * \return a value between min and max inclusive
 */
float clampF(float value, float min, float max);

/**
 * Normalize the value of an int
 * \param value the value to be clamped
 * \param min the minimum valid value
 * \param max the maximum valid value
 * \return a value between min and max inclusive
 */
int clampI(int value, int min, int max);

/**
 * Wait until the encoder gets above a certain a certain number of ticks
 * \param value the number of ticks the encoder should reach
 * \param encoder the encoder to wait on
 */
void waitEncoderGreater(int value, Encoder encoder);

/**
 * Wait until the encoder gets below a certain number of ticks
 * \param value the number of ticks for the encoder
 * \param encoder the encoder to wait on
 */
void waitEncoderLess(int value, Encoder encoder);


//Globals
AutoDriveMode drive_mode;
PIDHandle* gyro_pid;
PIDHandle* x_pid;
PIDHandle* y_pid;
PIDHandle* arm_pid;

Encoder e_right;
Encoder e_left;
Encoder e_arm;



#endif
