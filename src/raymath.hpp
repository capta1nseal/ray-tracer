#ifndef _RAYTRACERRAYMATH_
#define _RAYTRACERRAYMATH_


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

/*
azimuth and altitude will be between -pi and pi.
Any value passed into the initializer will be converted correctly from rad to rad.
Do conversions between degrees and rad yourself.
*/
struct Direction
{
    float azimuth;
    float altitude;

    Direction();
    Direction(float initAzimuth, float initAltitude);

    // outputs formatted angles to out stream
    friend std::ostream& operator<<(std::ostream& os, const Direction& direction);
};

/*
Encapsulates an origin point and direction.
Also implements some relevant mathematical operations.
*/
class Ray
{
public:
    Ray();
    Ray(Point& initOrigin, Direction& initDirection);
    Ray(float initX, float initY, float initZ, float initAzimuth, float initAltitude);

    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);

private:
    Point origin;
    Direction direction;
};


#endif
