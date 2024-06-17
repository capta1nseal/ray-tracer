#include "direction.hpp"


#include <ostream>
#include <cmath>

#include "orientation.hpp"
#include "vec3.hpp"


const float pi = M_PI;
const float tau = 2.0f * pi;


Direction::Direction(float initAzimuth, float initAltitude)
    : azimuth(initAzimuth), altitude(initAltitude)
{
    if (!std::isnormal(azimuth)) azimuth = 0.0f;
    if (!std::isnormal(altitude)) altitude = 0.0f;

    // TODO verify that fmod behaves as expected here
    azimuth = std::fmod(azimuth, tau);
    if (azimuth < -pi) azimuth += tau;
    else if (azimuth > pi) azimuth -= tau;
    altitude = std::fmod(altitude, tau);
    if (altitude < -pi) altitude += tau;
    else if (altitude > pi) altitude -= tau;
}
Direction::Direction(const Orientation& orientation)
    : Direction(orientation.yaw, orientation.pitch)
{    
}
Direction::Direction(const Vec3& direction)
{
    altitude = asin(direction.z);

    azimuth = asin(direction.y / sqrt(direction.x * direction.x + direction.y * direction.y));
}

std::ostream& operator<<(std::ostream& os, const Direction& direction)
{
    os << "(" << direction.azimuth << "," << direction.altitude << ")";
    return os;
}
