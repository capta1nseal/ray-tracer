#include "direction.hpp"


#include <ostream>

#include "orientation.hpp"


#include <cmath>
#include <math.h>


const float pi = M_PI;


Direction::Direction(float initAzimuth, float initAltitude)
    : azimuth(initAzimuth), altitude(initAltitude)
{
    if (!isnormal(azimuth)) azimuth = 0.0f;
    if (!isnormal(altitude)) altitude = 0.0f;

    // TODO verify that fmod behaves as expected here
    azimuth = std::fmod(azimuth, pi);
    altitude = std::fmod(altitude, pi);
}
Direction::Direction(const Orientation& orientation)
    : Direction(orientation.yaw, orientation.pitch)
{    
}

std::ostream& operator<<(std::ostream& os, const Direction& direction)
{
    os << "(" << direction.azimuth << "," << direction.altitude << ")";
    return os;
}
