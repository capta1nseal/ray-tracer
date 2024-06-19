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

        ResultType midDifference = std::sqrt(toCenter * toCenter - midDistance * midDistance);

        // Attempt to optimize by returning early if ray doesn't intersect 2D outline.
        if (midDifference > radius) return hitInfo;

        ResultType halfDepth = std::sqrt(radius * radius - midDifference * midDifference);

        hitInfo.distance = midDistance - halfDepth;
        // Select exit point if ray origin inside sphere.
        hitInfo.distance = (hitInfo.distance <= ResultType(0.0)) ? hitInfo.distance + ResultType(2.0) * halfDepth : hitInfo.distance;

        if (hitInfo.distance <= ResultType(0.0)) return hitInfo;

        hitInfo.didHit = true;

        hitInfo.hitPoint = ray.origin + hitInfo.distance * ray.direction;
        
        hitInfo.normal = (hitInfo.hitPoint - center).normalized();

        return hitInfo;
    }
};


#endif
