#ifndef _RAYTRACERSPHERE_
#define _RAYTRACERSPHERE_


#include "primitive.hpp"

#include <cmath>
#include <memory>

#include "../../raymath/raymath.hpp"


/*
3D sphere implementation.
Implements ray intersection.
*/
struct Sphere : public Primitive
{
    // Center point of sphere in global coordinates.
    Vec3<double> center;

    double radius;

    Sphere(const Vec3<double>& initCenter = {}, double initRadius = 1.0)
        : center(initCenter), radius(initRadius) {}
    
    std::unique_ptr<Primitive> clone() const override
    {
        return std::make_unique<Sphere>(*this);
    }

    HitInfo intersectRay(const Ray& ray) const override
    {
        HitInfo hitInfo;

        Vec3<double> toCenter = center - ray.origin;
        double midDistance = toCenter * ray.direction;

        // Squared to compare lengths without expensive sqrt.
        double midDifferenceSquared = toCenter * toCenter - midDistance * midDistance;
        double radiusSquared = radius * radius;

        // Return early if ray doesn't intersect forwards or backwards.
        if (midDifferenceSquared > radiusSquared) return hitInfo;

        double halfDepth = std::sqrt(radiusSquared - midDifferenceSquared);

        // Select entry point if it's in front of the ray origin, otherwise exit point.
        // Tolerance of a picometer to avoid light leaking.
        hitInfo.distance = (midDistance > halfDepth + 1.0e-12) ? midDistance - halfDepth : midDistance + halfDepth;

        // Treat as non-intersection if ray origin is too close to surface.
        if (hitInfo.distance <= 1.0e-12) return hitInfo;

        hitInfo.didHit = true;
        hitInfo.hitPoint = ray.origin + hitInfo.distance * ray.direction;

        // Normal facing in if ray origin inside sphere, otherwise out.
        hitInfo.normal = (midDistance > halfDepth) ? (hitInfo.hitPoint - center) * (1.0 / radius) : (center - hitInfo.hitPoint) * (1.0 / radius);

        return hitInfo;
    }
};


#endif
