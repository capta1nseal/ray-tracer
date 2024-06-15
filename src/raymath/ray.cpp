#include "ray.hpp"


#include <ostream>

#include "vec3.hpp"


Ray::Ray(const Vec3& initOrigin, const Vec3& initDirection)
    : origin(initOrigin), direction(initDirection)
{
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    os << ray.origin << "," << ray.direction;
    return os;
}
