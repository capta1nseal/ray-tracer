#ifndef _RAYTRACERDIRECTION_
#define _RAYTRACERDIRECTION_


#include <ostream>

struct Orientation;
struct Vec3;


/*
azimuth and altitude will be between -pi and pi.
Any value passed into the initializer will be converted correctly from rad to rad.
Do conversions between degrees and rad yourself.
Ensures values are normal fp values.
*/
struct Direction
{
    float azimuth, altitude;

    Direction(float initAzimuth = 0.0f, float initAltitude = 0.0f);
    Direction(const Orientation& orientation);
    Direction(const Vec3& direction);

    // outputs formatted direction to out stream
    friend std::ostream& operator<<(std::ostream& os, const Direction& direction);
};


#endif
