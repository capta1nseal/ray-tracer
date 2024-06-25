#ifndef _RAYTRACERDIRECTION_
#define _RAYTRACERDIRECTION_


#include <ostream>
#include <cmath>

#include "vec3.hpp"


const double pi = M_PI;
const double tau = 2.0 * pi;


/*
3D direction implementation.
Range of angles is [-pi,pi]
Call sanitize() in case edge-case floating point values must be avoided.
*/
template<Vec3Basis T>
struct Direction
{
    T azimuth, altitude;

    Direction(T initAzimuth = T(0.0), T initAltitude = T(0.0))
        : azimuth(initAzimuth), altitude(initAltitude)
    {
        conformAngles();
    }
    template<Vec3Basis U> Direction(const Direction<U>& other)
        : azimuth(other.azimuth), altitude(other.altitude) {}
    // direction given must be normalized.
    template<Vec3Basis U> Direction(const Vec3<U>& direction)
    {
        altitude = std::asin(direction.z);

        azimuth = -std::asin(direction.y / std::cos(altitude));
    }

    // returns normalized vector pointing forwards
    Vec3<T> forward() const
    {
        Vec3<T> forwardVec;

        forwardVec.z = std::sin(altitude);

        // x here temporarily stands for length of the direction vector projected onto the XY plane.
        forwardVec.x = std::cos(altitude);

        forwardVec.y = -std::sin(azimuth) * forwardVec.x;

        forwardVec.x = std::cos(azimuth) * forwardVec.x;

        return forwardVec;
    }

    void conformAngles()
    {
        azimuth = std::fmod(azimuth, tau);
        azimuth = (azimuth <-pi) ? azimuth + tau : azimuth;
        azimuth = (azimuth > pi) ? azimuth - tau : azimuth;
        altitude = std::fmod(altitude, tau);
        altitude = (altitude <-pi) ? altitude + tau : altitude;
        altitude = (altitude > pi) ? altitude - tau : altitude;
    }
    // Ensure all values represent actual numbers.
    // Any value not representing an actual number will be set to zero.
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
