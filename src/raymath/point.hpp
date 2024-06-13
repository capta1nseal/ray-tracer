#ifndef _RAYTRACERPOINT_
#define _RAYTRACERPOINT_


#include <ostream>


/*
trivial 3D point.
constructor should sanitise NaN.
*/
struct Point
{
    float x;
    float y;
    float z;

    Point();
    Point(float initX, float initY, float initZ);

    // outputs formatted coordinates to out stream
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};


#endif
