#include "camera.hpp"


#include "raymath/raymath.hpp"


#include <math.h>


Camera::Camera(const Point& initPosition, const Orientation& initOrientation, float initFocalLength, float initLensDiameter)
    : position(initPosition), orientation(initOrientation), focalLength(initFocalLength), lensDiameter(initLensDiameter)
{
    if (!isnormal(focalLength)) focalLength = 0.0f;
    if (!isnormal(lensDiameter)) lensDiameter = 0.0f;
}
Camera::Camera(const Ray& initRay, float initFocalLength, float initLensDiameter)
    : Camera(initRay.origin, Orientation(0.0f, initRay.direction.altitude, initRay.direction.azimuth), initFocalLength, initLensDiameter)
{
}
