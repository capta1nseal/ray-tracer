#include "ray.hpp"


#include <ostream>

#include "point.hpp"
#include "direction.hpp"


Ray::Ray()
{
    origin = Point();
    direction = Direction();
}
Ray::Ray(const Point& initOrigin, const Direction& initDirection)
    : origin(initOrigin), direction(initDirection)
{
}
Ray::Ray(float initX, float initY, float initZ, float initAzimuth, float initAltitude)
    : origin(Point(initX, initY, initZ)), direction(Direction(initAzimuth, initAltitude))
{
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    os << ray.origin << "," << ray.direction;
    return os;
}
