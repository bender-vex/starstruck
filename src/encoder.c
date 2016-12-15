#include <main.h>

/**
 Get total distance traveled in meters since last reset
 The diameter param should be in units of meters
 */
float getDistance(Encoder encoder, float diameter) {

    // Get distance of one rotation and multiply it by the number of rotations
    // the encoder has made
    float dis = PI * diameter;
    dis *= encoderGet(encoder) % 360;

    return dis;
}
