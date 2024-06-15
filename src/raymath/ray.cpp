#include "ray.hpp"


#include <ostream>

#include "vec3.hpp"


Ray::Ray(const Vec3& initOrigin, const Vec3& initDirection)
    : origin(initOrigin), direction(initDirection.normalized())
{
}

float Ray::distanceToPoint(const Vec3& point) const
{
    // TODO implement or delete
    return 0.0f;
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    os << ray.origin << "," << ray.direction;
    return os;
}
