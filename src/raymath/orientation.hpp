#ifndef _RAYTRACERORIENTATION_
#define _RAYTRACERORIENTATION_


#include <ostream>

struct Direction;
struct Vec3;


/*
Rather trivial 3D orientation implementation.
Range of angles is -pi to pi
Ensures values are normal fp values.
*/
struct Orientation
{
    float roll, pitch, yaw;

    Orientation(float initRoll = 0.0f, float initPitch = 0.0f, float initYaw = 0.0f);
    Orientation(const Direction& direction);

    // enforces angle range
    void conformAngles();

    // return normalized vector pointing forwards
    Vec3 forward() const;

    // returns normalized vector pointing up
    Vec3 up() const;

    Orientation operator+(const Orientation& other) const;
    Orientation operator-(const Orientation& other) const;

    // outputs formatted orientation to out stream
    friend std::ostream& operator<<(std::ostream& os, const Orientation& orientation);
};


#endif
