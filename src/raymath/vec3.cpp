#include "vec3.hpp"


#include "direction.hpp"
#include "orientation.hpp"


#include <math.h>
#include <iostream>

Vec3::Vec3(float initX, float initY, float initZ)
    : x(initX), y(initY), z(initZ)
{
    if (!isnormal(x)) x = 0.0f;
    if (!isnormal(y)) y = 0.0f;
    if (!isnormal(z)) z = 0.0f;
}
Vec3::Vec3(const Direction& direction)
{
    std::cout << direction.altitude << "\n";
    z = sinf32(direction.altitude);

    auto baseLength = sqrtf32(1.0f - z * z);

    y = sinf32(direction.azimuth) * baseLength;
    x = sqrtf32(baseLength * baseLength - y * y);
}
Vec3::Vec3(const Orientation& orientation)
    : Vec3(Direction(orientation))
{
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
Vec3 Vec3::operator/(const float& scalar) const
{
    return Vec3(x / scalar, y / scalar, z / scalar);
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
    x /= length;
    y /= length;
    z /= length;
}
Vec3 Vec3::normalized() const
{
    float length = (*this)();
    return Vec3(x / length, y / length, z / length);
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec3)
{
    os << "(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
    return os;
}
