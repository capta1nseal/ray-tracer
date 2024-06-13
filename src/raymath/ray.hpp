#ifndef _RAYTRACERRAY_
#define _RAYTRACERRAY_


#include <ostream>

#include "point.hpp"
#include "direction.hpp"


/*
Encapsulates an origin point and direction.
Also implements some relevant mathematical operations.
*/
class Ray
{
public:
    Ray();
    Ray(const Point& initOrigin, const Direction& initDirection);

    // outputs formatted origin-direction pair to out stream
    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);

private:
    Point origin;
    Direction direction;
};


#endif
