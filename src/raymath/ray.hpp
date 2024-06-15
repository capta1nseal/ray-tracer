#ifndef _RAYTRACERRAY_
#define _RAYTRACERRAY_


#include <ostream>

struct Vec3;


/*
Encapsulates an origin point and direction.
Also implements some relevant mathematical operations.
*/
struct Ray
{
    Vec3 origin, direction;

    Ray(const Vec3& initOrigin = Vec3(), const Vec3& initDirection = Vec3());

    // outputs formatted origin-direction pair to out stream
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};


#endif
