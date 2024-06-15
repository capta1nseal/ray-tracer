#ifndef _RAYTRACERVEC3_
#define _RAYTRACERVEC3_


#include <ostream>

struct Direction;
struct Orientation;


/*
Basic 3D vector.
Sanitised constructor inputs, other float inputs (including operator overloads) could cause problems.
Any attempt to divide by zero, including zero length normalization, will result in zero.
*/
struct Vec3
{
    float x, y, z;

    Vec3(float initX = 0.0f, float initY = 0.0f, float initZ = 0.0f);
    Vec3(const Direction& direction);
    Vec3(const Orientation& orientation);

    bool operator==(const Vec3& other) const;

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator+(const float& scalar) const;

    Vec3 operator-(const Vec3& other) const;
    Vec3 operator-(const float& scalar) const;

    Vec3 operator*(const float& scalar) const;
    float operator*(const Vec3& other) const;

    Vec3 operator/(const float& scalar) const;

    Vec3 operator%(const Vec3& other) const;

    void operator+=(const Vec3& other);
    void operator+=(const float& scalar);

    void operator-=(const Vec3& other);
    void operator-=(const float& scalar);

    void operator*=(const float& scalar);
    void operator/=(const float& scalar);

    // empty parantheses operator is magnitude
    float operator()() const;

    float dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;

    void normalize();
    Vec3 normalized() const;

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec3);
};


#endif
