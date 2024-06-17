#include "vec3.hpp"


#include <ostream>
#include <cmath>

#include "direction.hpp"
#include "orientation.hpp"


Vec3::Vec3(float initX, float initY, float initZ)
    : x(initX), y(initY), z(initZ)
{
    if (!std::isnormal(x)) x = 0.0f;
    if (!std::isnormal(y)) y = 0.0f;
    if (!std::isnormal(z)) z = 0.0f;
}
Vec3::Vec3(const Direction& direction)
{
    z = sinf32(direction.altitude);

    // x here temporarily stands for length of the direction vector projected onto the XY plane.
    x = cosf32(direction.altitude);

    y = sinf32(direction.azimuth) * x;
    x = cosf32(direction.azimuth) * x;
    
}
Vec3::Vec3(const Orientation& orientation)
{
    z = sinf32(orientation.pitch);
    // x here temporarily stands for length of the direction vector projected onto the XY plane.
    x = cosf32(orientation.pitch);

    y = sinf32(orientation.yaw) * x;
    x = cosf32(orientation.yaw) * x;
}

bool Vec3::operator==(const Vec3& other) const
{
    return x == other.x and y == other.y and z == other.z;
}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}
Vec3 Vec3::operator+(const float& scalar) const
{
    return Vec3(x + scalar, y + scalar, z + scalar);
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}
Vec3 Vec3::operator-(const float& scalar) const
{
    return Vec3(x - scalar, y - scalar, z - scalar);
}

Vec3 Vec3::operator*(const float& scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}
// operator* with Vec3 is dot product, cross product is operator%
float Vec3::operator*(const Vec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::operator/(const float& scalar) const
{
    if (scalar == 0.0f) return Vec3();
    return Vec3(x / scalar, y / scalar, z / scalar);
}
// operator% with Vec3 is cross product, dot product is operator*
Vec3 Vec3::operator%(const Vec3& other) const
{
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

void Vec3::operator+=(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
}
void Vec3::operator+=(const float& scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
}

void Vec3::operator-=(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}
void Vec3::operator-=(const float& scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
}

void Vec3::operator*=(const float& scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}
void Vec3::operator/=(const float& scalar)
{
    if (scalar == 0.0f) return;
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

float Vec3::operator()() const
{
    return sqrtf32(x * x + y * y + z * z);
}

void Vec3::normalize()
{
    float length = (*this)();
    if (length == 0.0f or length == 1.0f) return;
    x /= length;
    y /= length;
    z /= length;
}
Vec3 Vec3::normalized() const
{
    float length = (*this)();

    if (length == 0.0f) return Vec3();
    if (length == 1.0f) return *this;

    return Vec3(x / length, y / length, z / length);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec3)
{
    os << "(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
    return os;
}

Vec3 operator+(const float& scalar, const Vec3& vec3)
{
    return vec3 + scalar;
}
Vec3 operator-(const float& scalar, const Vec3& vec3)
{
    return Vec3(scalar - vec3.x, scalar - vec3.y, scalar - vec3.z);
}
Vec3 operator*(const float& scalar, const Vec3& vec3)
{
    return vec3 * scalar;
}
Vec3 operator/(const float& scalar, const Vec3& vec3)
{
    return Vec3(scalar / vec3.x, scalar / vec3.y, scalar / vec3.z);
}
