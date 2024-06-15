#ifndef _RAYTRACERCAMERA_
#define _RAYTRACERCAMERA_


#include <math.h>

#include "raymath/raymath.hpp"


/*
Wrapper for camera's spatial positioning and lens values.
*/
class Camera
{
public:
    Camera(
        const Vec3& initPosition = Vec3(), const Orientation& initOrientation = Orientation(),
        float initFocalLength = 50.0f, float initNearClip = 0.01f,
        float initAspectRatio = 16.0f/9.0f, float initHorizontalFOV = M_PI * 0.3f
    );

private:
    Vec3 position;
    Orientation orientation;
    // lengths in m
    // angles in rad
    float focalLength;
    float nearClip;
    float aspectRatio;
    float horizontalFOV;
    float verticalFOV;
};


#endif
