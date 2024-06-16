#ifndef _RAYTRACERSPHERE_
#define _RAYTRACERSPHERE_


#include "../../raymath/raymath.hpp"


/*
Geometric sphere in 3D space.
Implements ray intersection.
*/
struct Sphere
{
    // Center point of sphere in global coordinates.
    Vec3 center;

    float radius;

    Sphere(const Vec3& center = Vec3(), float radius = 1.0f);

    HitInfo intersectRay(const Ray& ray) const;
};


#endif
