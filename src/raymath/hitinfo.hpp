#ifndef _RAYTRACERHITINFO_
#define _RAYTRACERHITINFO_


#include "vec3.hpp"


/*
Wrapper for necessary information to get out of a ray intersection check.
Should be the return type for any ray intersection.
*/
struct HitInfo
{
    // didHit is true only if ray does actually intersect geometry in positive direction.
    bool didHit;
    // Distance to hitPoint. 0.0f never means an intersection.
    float distance;
    // Global position of ray's intersection with geometry.
    Vec3 hitPoint;
    // Normal vector in direction of incoming ray.
    Vec3 normal;
    // TODO implement material

    HitInfo();
};


#endif
