#include "plane.hpp"


#include <cmath>

#include "../../raymath/raymath.hpp"


Plane::Plane(const Vec3& initCorner, const Vec3& initEdge1, const Vec3& initEdge2)
    : corner(initCorner), edge1(initEdge1), edge2(initEdge2)
{
    // if any edge length is zero, the parameters do not define a shape.
    if (edge1() == 0.0f) edge2 = Vec3();
    if (edge2() == 0.0f) edge1 = Vec3();
}

HitInfo Plane::intersectRay(const Ray& ray) const
{
    HitInfo hitInfo;

    // Normal is first signed and not normalized, later surface normal.
    hitInfo.normal = edge1 % edge2;
    // Temporarily represents dot product of signed area and ray direction
    hitInfo.distance = hitInfo.normal * ray.direction;

    if (hitInfo.distance == 0.0f) return hitInfo;

    // Will be zero if edge vectors colinear.
    hitInfo.distance = (hitInfo.normal * (corner - ray.origin)) / hitInfo.distance;

    if (hitInfo.distance <= 0.0f) return hitInfo;

    hitInfo.hitPoint = ray.origin + (ray.direction * hitInfo.distance);

    // first local coordinates of hitPoint, then signed area vector between the local point and edge2.
    Vec3 area2 = hitInfo.hitPoint - corner;

    Vec3 area1 = edge1 % area2;
    area2 = area2 % edge2;

    // Check point is inside parallelogram in negative edge1 or edge2 direction.
    if (area1 * hitInfo.normal < 0.0f or area2 * hitInfo.normal < 0.0f) return hitInfo;

    // Check components of point along edge vectors are inside parallelogram in positive edge1 or edge2 direction.
    if (area1() / hitInfo.normal() > 1.0f or area2() / hitInfo.normal() > 1.0f) return hitInfo;

    hitInfo.didHit = true;
    hitInfo.normal.normalize();
    // Ensure normal opposes ray direction.
    hitInfo.normal = hitInfo.normal * (hitInfo.normal * ray.direction > 0.0f ? -1.0f : 1.0f);

    return hitInfo;
}
