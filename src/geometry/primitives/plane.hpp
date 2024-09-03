#ifndef _RAYTRACERPLANE_
#define _RAYTRACERPLANE_


#include "primitive.hpp"

#include <cmath>
#include <memory>

#include "../../raymath/raymath.hpp"


/*
Geometric planar parallelogram.
Implements ray intersection.
*/
struct Plane : public Primitive
{
    // Position of one rectangle corner from world origin. Acts as origin for edge1 and edge2.
    Vec3<double> corner;
    // Represents two parallel edges with origins of corner and corner + edge2.
    Vec3<double> edge1;
    // Represents two parallel edges with origins of corner and corner + edge1.
    Vec3<double> edge2;

    Plane(const Vec3<double>& initCorner = {}, const Vec3<double>& initEdge1 = {}, const Vec3<double>& initEdge2 = {})
        : corner(initCorner), edge1(initEdge1), edge2(initEdge2) {}

    std::unique_ptr<Primitive> clone() const override
    {
        return std::make_unique<Plane>(*this);
    }

    HitInfo intersectRay(const Ray& ray) const override
    {
        HitInfo hitInfo;

        // Normal is first signed and not normalized, later surface normal.
        hitInfo.normal = edge1 % edge2;
        // Temporarily represents dot product of signed area vector and ray direction.
        hitInfo.distance = hitInfo.normal * ray.direction;

        if (hitInfo.distance == 0.0) return hitInfo;

        hitInfo.distance = (hitInfo.normal * (corner - ray.origin)) / hitInfo.distance;

        if (hitInfo.distance <= 1.0e-12) return hitInfo;

        // Temporarily represents local coordinates of hitPoint.
        hitInfo.hitPoint = ray.origin + (ray.direction * hitInfo.distance) - corner;

        double subArea1 = (edge1 % hitInfo.hitPoint) * hitInfo.normal;
        double subArea2 = (hitInfo.hitPoint % edge2) * hitInfo.normal;
        double areaSquared = hitInfo.normal * hitInfo.normal;
        // Area of subparallelogram multiplied by area of full parallelogram through dot product is much cheaper than the sqrt in a magnitude call.
        // This can be compared with the full area squared to determine intersection.
        // If it is negative, it means the areas do not overlap, therefore the point is outside the parallelogram.
        if (subArea1 < 0.0 or subArea2 < 0.0 or subArea1 > areaSquared or subArea2 > areaSquared) return hitInfo;

        hitInfo.didHit = true;
        // Move hitPoint into global coordinates.
        hitInfo.hitPoint += corner;
        hitInfo.normal.normalize();
        // Ensure normal opposes ray direction.
        hitInfo.normal = (hitInfo.normal * ray.direction > 0.0 ? -hitInfo.normal : hitInfo.normal);

        return hitInfo;
    }
};


#endif
