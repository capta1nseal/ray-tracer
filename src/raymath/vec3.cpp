#include "vec3.hpp"


#include <math.h>


Vec3::Vec3(float initX, float initY, float initZ)
    : x(initX), y(initY), z(initZ)
{
    if (!isnormal(x)) x = 0.0f;
    if (!isnormal(y)) y = 0.0f;
    if (!isnormal(z)) z = 0.0f;
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
