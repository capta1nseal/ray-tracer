#include "sphere.hpp"


#include <math.h>

#include "../../raymath/raymath.hpp"


Sphere::Sphere(const Vec3& initCenter, float initRadius)
    : center(initCenter), radius(initRadius)
{
    if (!isnormal(radius)) radius = 1.0f;
}

HitInfo Sphere::intersectRay(const Ray& ray) const
{
    HitInfo hitInfo;

    Vec3 toCenter = center - ray.origin;

    float midDistance = toCenter * ray.direction;

    // Vec3 midPoint = ray.origin + midDistance * ray.direction;

    float midDifference = sqrt(toCenter * toCenter - midDistance * midDistance);

    // Attempt to optimize by returning early if ray doesn't intersect 2D outline.
    if (midDifference > radius) return hitInfo;

    hitInfo.didHit = true;

    float halfDepth = sqrt(radius * radius - midDifference * midDifference);

    hitInfo.distance = midDistance - halfDepth;
    // Check if ray origin inside sphere.
    hitInfo.distance += (hitInfo.distance <= 0.0f ? 2.0f : 0.0f) * halfDepth;

    hitInfo.hitPoint = ray.origin + hitInfo.distance * ray.direction;
    
    hitInfo.normal = (hitInfo.hitPoint - center).normalized();

    return hitInfo;
}
