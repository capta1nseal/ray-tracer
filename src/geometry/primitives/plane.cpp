#include "plane.hpp"


#include <cmath>

#include "../../raymath/raymath.hpp"


Plane::Plane(const Vec3& initCorner, const Vec3& initEdge1, const Vec3& initEdge2)
    : corner(initCorner), edge1(initEdge1), edge2(initEdge2)
{
    // if any edge length is zero, the parameters do not define a shape.
    if (edge1 == 0.0f) edge2 = Vec3();
    if (edge2 == 0.0f) edge1 = Vec3();
}

HitInfo Plane::intersectRay(const Ray& ray) const
{
    HitInfo hitInfo;

    // Normal is first signed and not normalized, later surface normal.
    hitInfo.normal = edge1 % edge2;
    // Temporarily represents dot product of signed area vector and ray direction
    hitInfo.distance = hitInfo.normal * ray.direction;

    if (hitInfo.distance == 0.0f) return hitInfo;

    hitInfo.distance = (hitInfo.normal * (corner - ray.origin)) / hitInfo.distance;

    if (hitInfo.distance <= 0.0f) return hitInfo;

    // temporarily represents local coordinates of hitPoint
    hitInfo.hitPoint = ray.origin + (ray.direction * hitInfo.distance) - corner;

    float subArea1 = (edge1 % hitInfo.hitPoint) * hitInfo.normal;
    float subArea2 = (hitInfo.hitPoint % edge2) * hitInfo.normal;
    float areaSquared = hitInfo.normal * hitInfo.normal;
    // Area of subparallelogram multiplied by area of full parallelogram through dot product is much cheaper than the sqrt in a magnitude call.
    // This can be compared with the full area squared to determine intersection.
    // If it is negative, it means the areas do not overlap, therefore the point is outside the parallelogram.
    if (subArea1 < 0.0f or subArea2 < 0.0f or subArea1 > areaSquared or subArea2 > areaSquared) return hitInfo;

    hitInfo.didHit = true;
    // move hitPoint into global coordinates
    hitInfo.hitPoint += corner;
    hitInfo.normal.normalize();
    // Ensure normal opposes ray direction.
    hitInfo.normal = (hitInfo.normal * ray.direction > 0.0f ? -hitInfo.normal : hitInfo.normal);

    return hitInfo;
}
