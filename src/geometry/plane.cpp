#include "plane.hpp"


#include "../raymath/raymath.hpp"


#include <math.h>


Plane::Plane(const Vec3& initCenter, const Vec3& initNormal, float initWidth, float initHeight)
    : center(initCenter), normal(initNormal), width(initWidth), height(initHeight)
{
    if (!isnormal(width)) width = 2.0f;
    if (!isnormal(height)) height = 2.0f;
}

bool Plane::intersectRay(const Ray& ray)
{
    // TODO implement
}
