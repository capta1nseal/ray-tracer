#ifndef _RAYTRACERORIENTATION_
#define _RAYTRACERORIENTATION_


#include <ostream>

struct Direction;


/*
Rather trivial 3D orientation implementation.
Range of angles is -pi to pi
Ensures values are normal fp values.
*/
struct Orientation
{
    float roll;
    float pitch;
    float yaw;

    Orientation(float initRoll = 0.0f, float initPitch = 0.0f, float initYaw = 0.0f);
    Orientation(const Direction& direction);

    // outputs formatted direction to out stream
    friend std::ostream& operator<<(std::ostream& os, const Orientation& orientation);
};


#endif
