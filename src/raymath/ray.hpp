#ifndef _RAYTRACERRAY_
#define _RAYTRACERRAY_


#include <ostream>

#include "vec3.hpp"


/*
Encapsulates an origin point and direction.
direction is expected to be passed in normalized.
Also implements some relevant mathematical operations.
*/
struct Ray
{
    Vec3<double> origin, direction;

    // initDirection expected to be normalized.
    Ray(const Vec3<double>& initOrigin = {}, const Vec3<double>& initDirection = {1.0, 0.0, 0.0})
        : origin(initOrigin), direction(initDirection) {}
};

template<Vec3Basis T>
std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    os << ray.origin << "," << ray.direction;
    return os;
}


#endif
