#include "camera.hpp"


#include "raymath/raymath.hpp"


#include <math.h>


Camera::Camera(const Point& initPosition, const Orientation& initOrientation, float initFocalLength, float initLensDiameter)
    : position(initPosition), orientation(initOrientation), focalLength(initFocalLength), lensDiameter(initLensDiameter)
{
    if (!isnormal(focalLength)) focalLength = 0.0f;
    if (!isnormal(lensDiameter)) lensDiameter = 0.0f;
}
