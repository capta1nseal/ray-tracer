#ifndef _RAYTRACERORIENTATION_
#define _RAYTRACERORIENTATION_


#include <ostream>


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

    Orientation();
    Orientation(float initRoll, float initPitch, float initYaw);

    // outputs formatted direction to out stream
    friend std::ostream& operator<<(std::ostream& os, const Orientation& orientation);
};


#endif
