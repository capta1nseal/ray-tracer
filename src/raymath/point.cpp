#include "point.hpp"


#include <ostream>


Point::Point()
{
    x = y = z = 0.0f;
}
Point::Point(float initX, float initY, float initZ)
    : x(initX), y(initY), z(initZ)
{
    if (x != x) x = 0.0f;
    if (y != y) y = 0.0f;
    if (z != z) z = 0.0f;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << "(" << point.x << "," << point.y << "," << point.z << ")";
    return os;
}
