#ifndef _RAYTRACERVEC3_
#define _RAYTRACERVEC3_


/*
Basic 3D vector.
Sanitised constructor inputs, other float inputs (including operator overloads) could cause problems.
*/
struct Vec3
{
    float x;
    float y;
    float z;

    Vec3(float initX = 0.0f, float initY = 0.0f, float initZ = 0.0f);

    bool operator==(const Vec3& other) const;

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator+(const float& scalar) const;

    Vec3 operator-(const Vec3& other) const;
    Vec3 operator-(const float& scalar) const;

    Vec3 operator*(const float& scalar) const;
    Vec3 operator/(const float& scalar) const;

    void operator+=(const Vec3& other);
    void operator+=(const float& scalar);

    void operator-=(const Vec3& other);
    void operator-=(const float& scalar);

    void operator*=(const float& scalar);
    void operator/=(const float& scalar);

    // magnitude
    float operator()() const;

    void normalize();
    Vec3 normalized() const;
};


#endif
