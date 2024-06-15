#include "plane.hpp"


#include "../raymath/raymath.hpp"


#include <math.h>


Plane::Plane(const Vec3& initCorner, const Vec3& initEdge1, const Vec3& initEdge2)
    : corner(initCorner), edge1(initEdge1), edge2(initEdge2)
{
    if (edge1() == 0.0f) edge2 = Vec3();
    if (edge2() == 0.0f) edge1 = Vec3();
}

bool Plane::intersectRay(const Ray& ray)
{
    // TODO implement
}
