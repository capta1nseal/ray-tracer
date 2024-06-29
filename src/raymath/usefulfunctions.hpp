#ifndef _RAYTRACERUSEFULFUNCTIONS_
#define _RAYTRACERUSEFULFUNCTIONS_


#include "vec3.hpp"
#include "direction.hpp"
#include "orientation.hpp"


/*
Some useful maths functions.
Mostly for operations on Vec3 objects, templated.
Sometimes syntactically neater than Vec3 member methods.
*/


const double oneThird = 0.3333333333333333333333333;

// Uses fast bitwise and logical operations to determine whether an unsigned int is a power of two.
// (has exactly one bit set)
bool isPowerOfTwo(unsigned int x);

// Uses fast bitwise and logical operations to determine whether an unsigned int is a power of two.
// This implementation skips a check for zero, so returns true also when x is zero.
bool isZeroOrPowerOfTwo(unsigned int x);

// Returns the sum of a single vector's elements.
template<Vec3Basis T>
auto sumElements(const Vec3<T>& vector)
{
    return vector.x + vector.y + vector.z;
}

// Returns the element-wise multiplication of two vectors.
// (as a vector, so not dot product)
template<Vec3Basis T, Vec3Basis U>
auto multiplyElements(const Vec3<T>& first, const Vec3<U>& second)
{
    return Vec3<std::common_type_t<T, U>>(first.x * second.x, first.y * second.y, first.z * second.z);
}

// Returns a vector that is moved from first towards second by factor.
// Doesn't expect anything specific of the values given, going outside the range [0,1] is well defined.
template<Vec3Basis T, Vec3Basis U>
auto lerp(const Vec3<T>& first, const Vec3<U>& second, std::common_type_t<T, U> factor)
{
    return Vec3<std::common_type_t<T, U>>(first + (factor * (second - first)));
}

// Returns a vector with each of given vector's values, clamped between min and max.
template<Vec3Basis T>
Vec3<T> clamp(const Vec3<T>& vector, T min, T max)
{
    return Vec3<T>(
        std::clamp(vector.x, min, max),
        std::clamp(vector.y, min, max),
        std::clamp(vector.z, min, max)
    );
}

// Reflects direction off normal's origin.
// Where direction faces into normal.
// Returns direction with same origin as normal.
template<Vec3Basis T, Vec3Basis U>
auto reflect(const Vec3<T>& direction, const Vec3<U>& normal)
{
    return Vec3<std::common_type_t<T, U>>(
        2.0 * (normal * -direction) * normal + direction
    );
}
// Reflects direction over normal's origin.
// Where direction and normal have the same origin.
// Returns direction with same origin as normal.
template<Vec3Basis T, Vec3Basis U>
auto reflectOut(const Vec3<T>& direction, const Vec3<U>& normal)
{
    return Vec3<std::common_type_t<T, U>>(
        2.0 * (normal * direction) * normal - direction
    );
}

// Returns element out of x,y,z with greatest magnitude.
// In case of equal magnitudes, order is x->y->z.
// You may wish to add your own checks in case order is very important.
template<Vec3Basis T>
T greatestElementByMagnitude(const Vec3<T>& vector)
{
    T xMag = std::abs(vector.x);
    T yMag = std::abs(vector.y);
    T zMag = std::abs(vector.z);
    if (xMag >= yMag and xMag >= zMag) return vector.x;
    if (yMag >= zMag) return vector.y;
    return vector.z;
}

// Returns mean of x,y,z.
template<Vec3Basis T>
T mean(const Vec3<T>& vector)
{
    return (vector.x + vector.y + vector.z) * T(oneThird);
}

// Returns mean of x,y,z's magnitudes.
template<Vec3Basis T>
T meanMagnitude(const Vec3<T>& vector)
{
    return (std::abs(vector.x) + std::abs(vector.y) + std::abs(vector.z)) * T(oneThird);
}

// Returns vector rotated around axis anticlockwise by angle.
template<Vec3Basis T, Vec3Basis U>
auto rotateAround(const Vec3<T>& vector, const Vec3<U>& axis, std::common_type_t<T, U> angle)
{
    using ResultType = std::common_type_t<T, U>;
    // Component of vector parallel to axis.
    Vec3<ResultType> parallelComponent = ((vector * axis) / (axis * axis)) * axis;
    // Component of vector perpendicular to axis.
    Vec3<ResultType> perpendicularComponent = vector - parallelComponent;
    // Vector perpendicular to perpendicular to axis and perpendicularComponent.
    Vec3<ResultType> thirdComponent = axis % perpendicularComponent;

    // sqrt of proportion between square lengths saves a sqrt compared to two magnitude calculations.
    return
        parallelComponent +
        std::cos(angle) * perpendicularComponent +
        std::sin(angle) * std::sqrt((perpendicularComponent * perpendicularComponent) / (thirdComponent * thirdComponent)) * thirdComponent;
}
// rotateAround requiring unit axis, saving some compute and memory.
// Returns vector rotated around axis anticlockwise by angle.
template<Vec3Basis T, Vec3Basis U>
auto rotateAroundUnit(const Vec3<T>& vector, const Vec3<U>& axis, std::common_type_t<T, U> angle)
{
    using ResultType = std::common_type_t<T, U>;
    // Component of vector parallel to axis.
    Vec3<ResultType> parallelComponent = (vector * axis) * axis;
    // Component of vector perpendicular to axis.
    Vec3<ResultType> perpendicularComponent = vector - parallelComponent;
    // Save memory just calculating third perpendicular component inline.

    return
        parallelComponent +
        (std::cos(angle) * perpendicularComponent) +
        (std::sin(angle) * (axis % perpendicularComponent));
}
// Returns vector pitched upwards relative to xy plane by pitch,
// this new vector is then rotated around itself anticlockwise by yaw.
template<Vec3Basis T>
auto rotateAroundSelf(const Vec3<T>& vector, T yaw, T pitch)
{
    double length = vector();
    return rotateAround(
        (Direction<T>(vector * (1.0 / length)) + Direction<T>(0.0, pitch)).forward() * length,
        vector,
        yaw
    );
}
// rotateAroundSelf requiring unit vector, saving some compute and memory.
// Returns vector pitched upwards relative to xy plane by pitch,
// this new vector is then rotated around itself anticlockwise by yaw.
template<Vec3Basis T>
auto rotateAroundSelfUnit(const Vec3<T>& vector, T yaw, T pitch)
{
    auto direction = Direction<T>(vector);
    return rotateAroundUnit(
        Direction<T>(direction.azimuth, direction.altitude + pitch).forward(),
        vector,
        yaw
    );
}


#endif
