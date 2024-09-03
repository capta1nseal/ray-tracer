#ifndef _RAYTRACERHITINFO_
#define _RAYTRACERHITINFO_


#include "vec3.hpp"
#include "../material.hpp"


/*
Wrapper for information about a ray intersection.
Should be the return type for any ray intersection.
If didHit is false, assume all other values to be invalid.
*/
struct HitInfo
{
    // didHit is true only in the case of an intersection.
    bool didHit;
    // Distance to hitPoint. 0.0f never means an intersection.
    double distance;
    // Global position of ray's intersection with geometry.
    Vec3<double> hitPoint;
    // Normal vector in direction of incoming ray.
    Vec3<double> normal;
    // Holds basic material properties.
    Material material;

    HitInfo()
    {
        didHit = false;
        distance = 0.0;
    }

    template<Vec3Basis U> HitInfo(const HitInfo& other)
        : didHit(other.didHit), distance(other.distance), hitPoint(other.hitPoint), normal(other.normal) {}
};


#endif
