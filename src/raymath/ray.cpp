#include "ray.hpp"


#include <ostream>

#include "point.hpp"
#include "direction.hpp"


Ray::Ray(const Point& initOrigin, const Direction& initDirection)
    : origin(initOrigin), direction(initDirection)
{
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    os << ray.origin << "," << ray.direction;
    return os;
}
