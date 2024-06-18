#include "orientation.hpp"


#include <ostream>
#include <cmath>

#include "direction.hpp"
#include "vec3.hpp"


const float pi = M_PI;
const float tau = 2.0f * pi;


Orientation::Orientation(float initRoll, float initPitch, float initYaw)
    : roll(initRoll), pitch(initPitch), yaw(initYaw)
{
    if (!std::isnormal(roll)) roll = 0.0f;
    if (!std::isnormal(pitch)) pitch = 0.0f;
    if (!std::isnormal(yaw)) yaw = 0.0f;

    conformAngles();
}
Orientation::Orientation(const Direction& direction)
    : Orientation(0.0f, direction.altitude, direction.azimuth)
{
}

void Orientation::conformAngles()
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

Vec3 Orientation::forward() const
{
    return *this;
}

Vec3 Orientation::up() const
{
    float cosRoll = cosf32(roll);
    float cosRollSinPitch = cosRoll * sinf32(pitch);
    float sinRoll = sinf32(roll);
    float sinYaw = sinf32(yaw);
    float cosYaw = cosf32(yaw);

    return {
        cosRollSinPitch * cosYaw + sinRoll * sinYaw,
        cosRollSinPitch * sinYaw - sinRoll * cosYaw,
        cosf32(pitch) * cosRoll
    };
}

Orientation Orientation::operator+(const Orientation& other) const
{
    return Orientation(roll + other.roll, pitch + other.pitch, yaw + other.yaw);
}
Orientation Orientation::operator-(const Orientation& other) const
{
    return Orientation(roll - other.roll, pitch - other.pitch, yaw - other.yaw);
}

std::ostream& operator<<(std::ostream& os, const Orientation& orientation)
{
    os << "(" << orientation.roll << "," << orientation.pitch << "," << orientation.yaw << ")";
    return os;
}
