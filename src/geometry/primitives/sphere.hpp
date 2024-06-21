#ifndef _RAYTRACERSPHERE_
#define _RAYTRACERSPHERE_


#include <cmath>

#include "../../raymath/raymath.hpp"


/*
Geometric sphere in 3D space.
Implements ray intersection.
Values passed in must be normal floating point values.
*/
template<Vec3Basis T>
struct Sphere
{
    // Center point of sphere in global coordinates.
    Vec3<T> center;

    T radius;

    Sphere(const Vec3<T>& initCenter = {}, T initRadius = T(1.0))
        : center(initCenter), radius(initRadius) {}
    template<Vec3Basis U> Sphere(const Sphere<U>& other)
        : center(other.center), radius(other.radius) {}

    template<Vec3Basis U> auto intersectRay(const Ray<U>& ray) const
    {
        using ResultType = std::common_type_t<T, U>;
        
        HitInfo<ResultType> hitInfo;

        Vec3<ResultType> toCenter = center - ray.origin;

        ResultType midDistance = toCenter * ray.direction;

        // squared to compare lengths without expensive sqrt
        ResultType midDifferenceSquared = toCenter * toCenter - midDistance * midDistance;

        // squared to compare lengths without expensive sqrt
        ResultType radiusSquared = radius * radius;

        // Attempt to optimize by returning early if ray doesn't intersect 2D outline.
        if (midDifferenceSquared > radiusSquared) return hitInfo;

        ResultType halfDepth = std::sqrt(radiusSquared - midDifferenceSquared);

        // Select exit point first to check if ray origin is too far forward.
        hitInfo.distance = midDistance + halfDepth;

        if (hitInfo.distance <= ResultType(1.0e-9)) return hitInfo;

        // Select entry point if ray origin is behind it.
        hitInfo.distance = (hitInfo.distance > halfDepth + halfDepth) ? hitInfo.distance - (halfDepth + halfDepth) : hitInfo.distance;

        hitInfo.didHit = true;

        hitInfo.hitPoint = ray.origin + hitInfo.distance * ray.direction;
        
        hitInfo.normal = (hitInfo.hitPoint - center).normalized();

        return hitInfo;
    }
};


#endif
