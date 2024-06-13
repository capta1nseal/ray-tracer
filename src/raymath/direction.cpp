#include "direction.hpp"


#include <ostream>


#include <cmath>


const float pi = M_PI;


Direction::Direction()
{
    azimuth = altitude = 0.0f;
}
Direction::Direction(float initAzimuth, float initAltitude)
    : azimuth(initAzimuth), altitude(initAltitude)
{
    if (azimuth != azimuth) azimuth = 0.0f;
    if (altitude != altitude) altitude = 0.0f;

    // TODO verify that fmod behaves as expected here
    azimuth = std::fmod(azimuth, pi);
    altitude = std::fmod(altitude, pi);
}

std::ostream& operator<<(std::ostream& os, const Direction& direction)
{
    os << "(" << direction.azimuth << "," << direction.altitude << ")";
    return os;
}
