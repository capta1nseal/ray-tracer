#ifndef _RAYTRACERDIRECTION_
#define _RAYTRACERDIRECTION_


#include <ostream>

struct Orientation;
struct Vec3;


/*
azimuth and altitude will be between -pi and pi.
Any value passed into the initializer will be converted correctly from rad to [-pi, pi] rad.
Do conversions between degrees and rad yourself.
Call sanitize() if you have any doubt about floating point garbage states.
*/
struct Direction
{
    float azimuth, altitude;

    Direction(float initAzimuth = 0.0f, float initAltitude = 0.0f);
    Direction(const Orientation& orientation);
    // direction given must be normalized.
    Direction(const Vec3& direction);

    void sanitize();

    // outputs formatted direction to out stream
    friend std::ostream& operator<<(std::ostream& os, const Direction& direction);
};


#endif
