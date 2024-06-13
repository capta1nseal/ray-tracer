#ifndef _RAYTRACERRAY_
#define _RAYTRACERRAY_


#include <ostream>

#include "point.hpp"
#include "direction.hpp"


/*
Encapsulates an origin point and direction.
Also implements some relevant mathematical operations.
*/
struct Ray
{
    Point origin;
    Direction direction;

    Ray(const Point& initOrigin = Point(), const Direction& initDirection = Direction());

    // outputs formatted origin-direction pair to out stream
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
};


#endif
