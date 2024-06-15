#include "plane.hpp"


#include "../raymath/raymath.hpp"


#include <math.h>
#include <iostream>


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

    // check if ray is parallel to or moving away from plane of parallelogram.
    if (angleProduct == 0.0f) return 0.0f;

    /*
    normal here is very handy.
    the plane of the parallelogram is defined as:
        normal.x(x-corner.x) + normal.y(y-corner.y) + normal.z(z-corner.z) = 0.
    This is very useful to find a point on ray (ray.origin + d * ray.direction) for which the plane equation is true.
    The return equation then solves for d.
    */
    return (normal * (corner - ray.origin)) / angleProduct;
}
