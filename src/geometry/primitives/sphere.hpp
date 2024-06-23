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

        // Squared to compare lengths without expensive sqrt.
        ResultType midDifferenceSquared = toCenter * toCenter - midDistance * midDistance;
        ResultType radiusSquared = radius * radius;

        // Return early if ray doesn't intersect forwards or backwards.
        if (midDifferenceSquared > radiusSquared) return hitInfo;

        ResultType halfDepth = std::sqrt(radiusSquared - midDifferenceSquared);

        // Select entry point if it's in front of the ray origin, otherwise exit point.
        // Tolerance of a picometer to avoid light leaking.
        hitInfo.distance = (midDistance > halfDepth + ResultType(1.0e-12)) ? midDistance - halfDepth : midDistance + halfDepth;

        // Treat as non-intersection if ray origin is too close to surface.
        if (hitInfo.distance <= ResultType(1.0e-12)) return hitInfo;

        hitInfo.didHit = true;
        hitInfo.hitPoint = ray.origin + hitInfo.distance * ray.direction;

        // Normal facing in if ray origin inside sphere, otherwise out.
        hitInfo.normal = (midDistance > halfDepth) ? (hitInfo.hitPoint - center) * (1.0 / radius) : (center - hitInfo.hitPoint) * (1.0 / radius);

        return hitInfo;
    }
};


#endif
