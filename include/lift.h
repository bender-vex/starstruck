/** \file lift.h
 * \brief Control of the mechanism for hanging
 */

#ifndef LIFT_H_
#define LIFT_H_

#include "API.h"

#define LIFT_SIDE 5
#define LIFT_TOP 7
#define LIFT_BOTTOM 6

/**
 * Set speed of lift motors
 * \param power motor speed
 */
void liftPower(int power);

#endif // include guard
