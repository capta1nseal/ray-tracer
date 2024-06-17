#ifndef _RAYTRACERCAMERA_
#define _RAYTRACERCAMERA_


#include <cmath>

#include "raymath/raymath.hpp"
#include "geometry/primitives/plane.hpp"


/*
Wrapper for camera's spatial positioning and lens values.
*/
class Camera
{
public:
    Camera(
        const Vec3& initPosition = Vec3(), const Orientation& initOrientation = Orientation(),
        unsigned int initWidth = 1920, unsigned int initHeight = 1080,
        float initHorizontalFOV = 49.0*M_PI/180.0
    );

    float getWidth() const;
    float getHeight() const;

    Plane getTargetPlane() const;

    Ray getRayToPixel(unsigned int x, unsigned int y) const;

private:
    Vec3 position;
    Orientation orientation;

    // lengths in m
    // angles in rad

    unsigned int width;
    unsigned int height;
    float aspectRatio;
    float horizontalFOV;
    float verticalFOV;

    // rays will be cast towards this plane, centered exactly 1 m in front of the camera.
    // the origin of the plane will be in the bottom left from the perspective of the camera.
    Plane targetPlane;
};


#endif
