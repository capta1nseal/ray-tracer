#include "raymath.hpp"


#include <ostream>


#include <cmath>


const float pi = 1.0f * M_PI;
const float tau = 2.0f * M_PI;


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



Direction::Direction()
{
    azimuth = altitude = 0.0f;
}
Direction::Direction(float initAzimuth, float initAltitude)
    : azimuth(initAzimuth), altitude(initAltitude)
{
    if (azimuth != azimuth) azimuth = 0.0f;
    if (altitude != altitude) altitude = 0.0f;

    // TODO verify that fmod behaves as expected here
    azimuth = std::fmod(azimuth, pi);
    altitude = std::fmod(altitude, pi);
}

std::ostream& operator<<(std::ostream& os, const Direction& direction)
{
    os << "(" << direction.azimuth << "," << direction.altitude << ")";
    return os;
}



Ray::Ray()
{
    origin = Point();
    direction = Direction();
}
Ray::Ray(Point& initOrigin, Direction& initDirection)
    : origin(initOrigin), direction(initDirection)
{
}
Ray::Ray(float initX, float initY, float initZ, float initAzimuth, float initAltitude)
    : origin(Point(initX, initY, initZ)), direction(Direction(initAzimuth, initAltitude))
{
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
    os << ray.origin << "\n" << ray.direction;
    return os;
}
