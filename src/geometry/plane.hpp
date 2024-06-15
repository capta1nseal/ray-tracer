#ifndef _RAYTRACERPLANE_
#define _RAYTRACERPLANE_


#include "../raymath/raymath.hpp"


/*
Geometric rectangle on a plane.
Implements boolean ray intersection check.
*/
struct Plane
{
    Vec3 center, normal;
    // width, height in m
    float width, height;

    Plane(const Vec3& initCenter = Vec3(), const Vec3& initNormal = Vec3(), float width = 2.0f, float height = 2.0f);

    bool intersectRay(const Ray& ray);
};


#endif
