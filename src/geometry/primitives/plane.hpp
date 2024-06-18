#ifndef _RAYTRACERPLANE_
#define _RAYTRACERPLANE_


#include <cmath>

#include "../../raymath/raymath.hpp"


/*
Geometric parallelogram on a plane.
Implements ray intersection.
*/
template<Vec3Basis T>
struct Plane
{
    // Position of one rectangle corner from world origin. Acts as origin for edge1 and edge2.
    Vec3<T> corner;
    // Represents two parallel edges with origins of corner and corner + edge2.
    Vec3<T> edge1;
    // Represents two parallel edges with origins of corner and corner + edge1.
    Vec3<T> edge2;

    Plane(const Vec3<T>& initCorner = {}, const Vec3<T>& initEdge1 = {}, const Vec3<T>& initEdge2 = {})
        : corner(initCorner), edge1(initEdge1), edge2(initEdge2) {}
    template<Vec3Basis U> Plane(const Plane<U>& other)
        : corner(other.corner), edge1(other.edge1), edge2(other.edge2) {}

    template<Vec3Basis U> auto intersectRay(const Ray<U>& ray) const
    {
        using ResultType = std::common_type_t<T, U>;

        HitInfo<ResultType> hitInfo;

        // Normal is first signed and not normalized, later surface normal.
        hitInfo.normal = edge1 % edge2;
        // Temporarily represents dot product of signed area vector and ray direction.
        hitInfo.distance = hitInfo.normal * ray.direction;

        if (hitInfo.distance == ResultType(0.0)) return hitInfo;

        hitInfo.distance = (hitInfo.normal * (corner - ray.origin)) / hitInfo.distance;

        if (hitInfo.distance <= ResultType(0.0)) return hitInfo;

        // Temporarily represents local coordinates of hitPoint.
        hitInfo.hitPoint = ray.origin + (ray.direction * hitInfo.distance) - corner;

        ResultType subArea1 = (edge1 % hitInfo.hitPoint) * hitInfo.normal;
        ResultType subArea2 = (hitInfo.hitPoint % edge2) * hitInfo.normal;
        ResultType areaSquared = hitInfo.normal * hitInfo.normal;
        // Area of subparallelogram multiplied by area of full parallelogram through dot product is much cheaper than the sqrt in a magnitude call.
        // This can be compared with the full area squared to determine intersection.
        // If it is negative, it means the areas do not overlap, therefore the point is outside the parallelogram.
        if (subArea1 < ResultType(0.0) or subArea2 < ResultType(0.0) or subArea1 > areaSquared or subArea2 > areaSquared) return hitInfo;

        hitInfo.didHit = true;
        // Move hitPoint into global coordinates.
        hitInfo.hitPoint += corner;
        hitInfo.normal.normalize();
        // Ensure normal opposes ray direction.
        hitInfo.normal = (hitInfo.normal * ray.direction > ResultType(0.0) ? -hitInfo.normal : hitInfo.normal);

        return hitInfo;
    }
};


#endif
