#include "lift.h"

void liftPower(int power) {
	// positive values lift robot up
	
	motorSet(LIFT_TOP, -power);
	motorSet(LIFT_BOTTOM, power);
	motorSet(LIFT_SIDE, power);
}
