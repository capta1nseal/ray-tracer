#ifndef _RAYTRACERDIRECTION_
#define _RAYTRACERDIRECTION_


#include <ostream>
#include <cmath>

#include "vec3.hpp"


const double pi = M_PI;
const double tau = 2.0 * pi;


/*
azimuth and altitude will be between -pi and pi.
Any value passed into the initializer will be converted correctly from rad to [-pi, pi] rad.
Do conversions between degrees and rad yourself.
Call sanitize() if you have any doubt about floating point garbage states.
*/
template<Vec3Basis T>
struct Direction
{
    T azimuth, altitude;

    Direction(T initAzimuth = T(0.0), T initAltitude = T(0.0))
        : azimuth(initAzimuth), altitude(initAltitude)
    {
        azimuth = std::fmod(azimuth, tau);
        azimuth = (azimuth <-pi) ? azimuth + tau : azimuth;
        azimuth = (azimuth > pi) ? azimuth - tau : azimuth;
        altitude = std::fmod(altitude, tau);
        altitude = (altitude <-pi) ? altitude + tau : altitude;
        altitude = (altitude > pi) ? altitude - tau : altitude;
    }
    template<Vec3Basis U> Direction(const Direction<U>& other)
        : azimuth(other.azimuth), altitude(other.altitude) {}
    // direction given must be normalized.
    template<Vec3Basis U> Direction(const Vec3<U>& direction)
    {
        altitude = std::asin(-direction.z);

        azimuth = std::asin(direction.y / std::cos(altitude));
    }

    void sanitize()
    {
        if (!std::isnormal(azimuth)) azimuth = T(0.0);
        if (!std::isnormal(altitude)) altitude = T(0.0);
    }
};

template<Vec3Basis T> std::ostream& operator<<(std::ostream& os, const Direction<T>& direction)
{
    os << "(" << direction.azimuth << "," << direction.altitude << ")";
    return os;
}

#endif
