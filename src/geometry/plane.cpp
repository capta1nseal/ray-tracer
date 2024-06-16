#include "plane.hpp"


#include <math.h>

#include "../raymath/raymath.hpp"


Plane::Plane(const Vec3& initCorner, const Vec3& initEdge1, const Vec3& initEdge2)
    : corner(initCorner), edge1(initEdge1), edge2(initEdge2)
{
    // if any edge length is zero, the parameters do not define a shape.
    if (edge1() == 0.0f) edge2 = Vec3();
    if (edge2() == 0.0f) edge1 = Vec3();
}

float Plane::intersectRay(const Ray& ray) const
{
    auto normal = edge1 % edge2;
    auto angleProduct = normal * ray.direction;

    // Check if ray is parallel to plane of parallelogram.
    if (angleProduct == 0.0f) return 0.0f;

    /*
    Normal here is very handy.
    The plane of the parallelogram is defined as:
        normal.x(x-corner.x) + normal.y(y-corner.y) + normal.z(z-corner.z) = 0.
    This is very useful to find a point on ray (ray.origin + d * ray.direction) for which the plane equation is true.
    The following equation then solves for d.
    */

    float distance = (normal * (corner - ray.origin)) / angleProduct;

    // if the geometry clips through the ray origin or is behind the ray origin, return early to save work
    if (distance <= 0.0f) return distance;

    /*
    Finding the intersection:
    The area or a parallelogram is the magnitude of the cross product of two adjacent side vectors.
    Switching one of these vectors with the vector from the corner to the point of interest,
        then dividing by the area of the actual shape, gives the component of the point in the direction of the switched out vector.
    The other can then be switched in as well, giving both components.
    If the point is in the negative direction outside the area being checked,
        the intersection must be eliminated by checking signs of dot products of the cross products of edge/point pairings.
    Otherwise, the components can just be checked to be less than 1.
    */

    Vec3 localPoint = ray.origin + (ray.direction * distance) - corner;

    Vec3 area = edge1 % edge2;
    Vec3 area1 = edge1 % localPoint;
    Vec3 area2 = localPoint % edge2;

    if (area1 * area < 0.0f or area2 * area < 0.0f) return 0.0f;

    float component1 = area1() / area();

    float component2 = area2() / area();

    if (component1 > 1.0f or component2 > 1.0f) return 0.0f;

    return distance;
}
