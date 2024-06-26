#include "vec3.hpp"


template<Vec3Basis T, Vec3Basis U>
auto multiplyElements(const Vec3<T>& first, const Vec3<U> second)
{
    return Vec3<std::common_type_t<T, U>>(first.x * second.x, first.y * second.y, first.z * second.z);
}

template<Vec3Basis T, Vec3Basis U>
auto lerp(const Vec3<T>& first, const Vec3<U>& second, std::common_type_t<T, U> factor)
{
    return Vec3<std::common_type_t<T, U>>(first + (factor * (second - first)));
}

template<Vec3Basis T>
Vec3<T> clamp(const Vec3<T>& value, T min, T max)
{
    return Vec3<T>(
        std::clamp(value.x, min, max),
        std::clamp(value.y, min, max),
        std::clamp(value.z, min, max)
    );
}

// Reflects dir off normal's origin.
// Expects dir to be facing in to normal's origin
template<Vec3Basis T, Vec3Basis U>
auto reflect(const Vec3<T>& dir, const Vec3<U>& normal)
{
    return dir.reflected(normal);
}

// Returns number out of x,y,z with greatest magnitude.
template<Vec3Basis T>
T furthestAxisValue(const Vec3<T>& vector)
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
    return (vector.x + vector.y + vector.z) / T(3.0);
}

// Returns mean of x,y,z's magnitudes.
template<Vec3Basis T>
T meanMagnitude(const Vec3<T>& vector)
{
    return (std::abs(vector.x) + std::abs(vector.y) + std::abs(vector.z)) / T(3.0);
}
