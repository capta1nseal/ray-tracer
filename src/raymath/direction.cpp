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
    azimuth = std::fmod(azimuth, tau);
    azimuth = (azimuth <-pi) ? azimuth + tau : azimuth;
    azimuth = (azimuth > pi) ? azimuth - tau : azimuth;
    altitude = std::fmod(altitude, tau);
    altitude = (altitude <-pi) ? altitude + tau : altitude;
    altitude = (altitude > pi) ? altitude - tau : altitude;
}
Direction::Direction(const Orientation& orientation)
    : Direction(orientation.yaw, orientation.pitch)
{    
}
Direction::Direction(const Vec3& direction)
{
    altitude = asin(-direction.z);

    azimuth = asin(direction.y / cosf32(altitude));
}

void Direction::sanitize()
{
    if (!std::isnormal(azimuth)) azimuth = 0.0f;
    if (!std::isnormal(altitude)) altitude = 0.0f;
}

std::ostream& operator<<(std::ostream& os, const Direction& direction)
{
    os << "(" << direction.azimuth << "," << direction.altitude << ")";
    return os;
}
