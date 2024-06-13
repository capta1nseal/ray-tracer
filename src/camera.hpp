#ifndef _RAYTRACERCAMERA_
#define _RAYTRACERCAMERA_


#include "raymath/raymath.hpp"


/*
Wrapper for camera's spatial positioning and lens values.
*/
class Camera
{
public:
    Camera(
        const Point& initPosition = Point(), const Orientation& initOrientation = Orientation(),
        float initFocalLength = 50.0f, float initLensDiameter = 30.0f
    );
    Camera(const Ray& initRay = Ray(), float initFocalLength = 50.0f, float initLensDiameter = 30.0f);

private:
    Point position;
    Orientation orientation;
    // lengths in mm
    float focalLength;
    float lensDiameter;
};


#endif
