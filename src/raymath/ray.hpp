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
    Vec3 origin, direction;

    // initDirection must be normalized.
    Ray(const Vec3& initOrigin = Vec3(), const Vec3& initDirection = Vec3(1.0f, 0.0f, 0.0f));

    // Distance to a point, ensure they're in the same coordinate system.
    float distanceToPoint(const Vec3& point) const;

    // outputs formatted origin,direction pair to out stream.
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};


#endif
