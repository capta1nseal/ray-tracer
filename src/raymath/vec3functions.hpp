#include "vec3.hpp"


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

// reflects dir off normal's origin.
// Expects dir to be facing in to normal's origin
template<Vec3Basis T, Vec3Basis U>
auto reflect(const Vec3<T>& dir, const Vec3<U>& normal)
{
    return dir.reflected(normal);
}