#include "orientation.hpp"


#include <ostream>


#include <cmath>
#include <math.h>


const float pi = M_PI;


Orientation::Orientation()
{
    roll = pitch = yaw = 0.0f;
}
Orientation::Orientation(float initRoll, float initPitch, float initYaw)
    : roll(initRoll), pitch(initPitch), yaw(initYaw)
{
    if (!isnormal(roll)) roll = 0.0f;
    if (!isnormal(pitch)) pitch = 0.0f;
    if (!isnormal(yaw)) yaw = 0.0f;

    roll = std::fmod(roll, pi);
    pitch = std::fmod(pitch, pi);
    yaw = std::fmod(yaw, pi);
}

std::ostream& operator<<(std::ostream& os, const Orientation& orientation)
{
    os << "(" << orientation.roll << "," << orientation.pitch << "," << orientation.yaw << ")";
    return os;
}
