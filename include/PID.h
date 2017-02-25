/** \file PID.h
 * \brief Multi-purpose PID controllers
 */

#ifndef PID_H_
#define PID_H_

#include <math.h>
#include <API.h>
#include <string.h>
#include <drive.h>

typedef struct
{
	float kp; // P constant
	float ki; // I constant
	float kd; // D constant
	float target; //The value we want to reach
	float last_error;
	float error_cap;
	float integral;
} PIDHandle;

/**
 * Initialize a PIDHandle
 * \param kp proportional constant
 * \param ki integral constant
 * \param kd derivative constant
 * \param target value to reach
 * \param error_cap max error
 * \return pointer to PIDHandle
 */
PIDHandle* initPID(float kp, float ki, float kd, float target, float error_cap);

/**
 * Set the target for a PID handle
 * \param handle pointer to the PID handle which should be modified
 * \param target the target to set
 */
void setPIDTarget(PIDHandle* handle, float target);

/**
 * Destroy PIDHandle
 * \param handle the PIDHandle to destroy
 */
void freePID(PIDHandle* handle);

/**
 * Calculate an output PID value
 * \param handle pointer to the PID handle which should be used for calculation
 * \param position current value
 * \return output PID value
 */
float calculatePID(PIDHandle* handle, float position);



#endif
