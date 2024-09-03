#ifndef _RAYTRACERORIENTATION_
#define _RAYTRACERORIENTATION_


#include <ostream>
#include <cmath>

#include "vec3.hpp"


/*
3D orientation implementation.
Range of angles is [-pi,pi]
Call sanitize() in case edge-case floating point values must be avoided.
*/
template<Vec3Basis T>
struct Orientation
{
    T roll, pitch, yaw;

    Orientation(T initRoll = T(0.0), T initPitch = T(0.0), T initYaw = T(0.0))
        : roll(initRoll), pitch(initPitch), yaw(initYaw)
    {
        conformAngles();
    }
    template<Vec3Basis U> Orientation(const Orientation<U>& other)
        : roll(other.roll), pitch(other.pitch), yaw(other.yaw) {}
    template<Vec3Basis U> Orientation(Vec3<U> direction)
    {
        roll = 0.0;

        pitch = std::asin(direction.z);

        yaw = -std::acos(direction.x / std::cos(pitch));
    }

    // returns normalized vector pointing forwards
    Vec3<T> forward() const
    {
        Vec3<T> forwardVec;

        forwardVec.z = std::sin(pitch);

        // x here temporarily stands for length of the direction vector projected onto the XY plane.
        forwardVec.x = std::cos(pitch);

        forwardVec.y = -std::sin(yaw) * forwardVec.x;

        forwardVec.x = std::cos(yaw) * forwardVec.x;

        return forwardVec;
    }

    // returns normalized vector pointing up
    Vec3<T> up() const
    {
        T cosRoll = std::cos(roll);
        T minusCosRollSinPitch = -cosRoll * std::sin(pitch);
        T sinRoll = std::sin(roll);
        T sinYaw = std::sin(yaw);
        T cosYaw = std::cos(yaw);

        return Vec3(
            minusCosRollSinPitch * cosYaw + sinRoll * sinYaw,
            minusCosRollSinPitch * -sinYaw + sinRoll * cosYaw,
            std::cos(pitch) * cosRoll
        );
    }

    template<Vec3Basis U> auto operator+(const Orientation<U>& other) const
    { return Orientation<std::common_type_t<T, U>>(roll + other.roll, pitch + other.pitch, yaw + other.yaw); }
    
    template<Vec3Basis U> auto operator-(const Orientation<U>& other) const
    { return Orientation<std::common_type_t<T, U>>(roll - other.roll, pitch - other.pitch, yaw - other.yaw); }

    // Enforce angle ranges correctly wrapped into [-pi,pi]
    void conformAngles()
    {
        roll = std::fmod(roll, tau);
        roll = (roll <-pi) ? roll + tau : roll;
        roll = (roll > pi) ? roll - tau : roll;
        pitch = std::fmod(pitch, tau);
        pitch = (pitch <-pi) ? pitch + tau : pitch;
        pitch = (pitch > pi) ? pitch - tau : pitch;
        yaw = std::fmod(yaw, tau);
        yaw = (yaw <-pi) ? yaw + tau : yaw;
        yaw = (yaw > pi) ? yaw - tau : yaw;
    }
    // Ensure all values represent actual numbers.
    // Any value not representing an actual number will be set to zero.
    void sanitize()
    {
        if (!std::isnormal(roll)) roll = T(0.0);
        if (!std::isnormal(pitch)) pitch = T(0.0);
        if (!std::isnormal(yaw)) yaw = T(0.0);
    }
};

// Output orientation to os formatted as (roll,pitch,yaw).
template<Vec3Basis T> std::ostream& operator<<(std::ostream& os, const Orientation<T>& orientation)
{
    os << "(" << orientation.roll << "," << orientation.pitch << "," << orientation.yaw << ")";
    return os;
}


#endif
