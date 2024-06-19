#ifndef _RAYTRACERRAY_
#define _RAYTRACERRAY_


#include <ostream>

#include "vec3.hpp"


/*
Encapsulates an origin point and direction.
direction is expected to be passed in normalized.
Also implements some relevant mathematical operations.
*/
template<Vec3Basis T>
struct Ray
{
    Vec3<T> origin, direction;

    // initDirection must be normalized.
    Ray(const Vec3<T>& initOrigin = {}, const Vec3<T>& initDirection = {1.0, 0.0, 0.0})
        : origin(initOrigin), direction(initDirection) {}
    
    template<Vec3Basis U> Ray(const Ray<U>& other)
        : origin(other.origin), direction(other.direction) {}
};

template<Vec3Basis T>
std::ostream& operator<<(std::ostream& os, const Ray<T>& ray)
{
    os << ray.origin << "," << ray.direction;
    return os;
}


#endif
