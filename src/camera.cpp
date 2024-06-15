#include "camera.hpp"


#include "raymath/raymath.hpp"


#include <math.h>


Camera::Camera(const Vec3& initPosition, const Orientation& initOrientation, float initFocalLength, float initNearClip, float initAspectRatio, float initHorizontalFOV)
    : position(initPosition), orientation(initOrientation), focalLength(initFocalLength), nearClip(initNearClip), aspectRatio(initAspectRatio), horizontalFOV(initHorizontalFOV)
{
    if (!isnormal(focalLength)) focalLength = 50.0f;
    if (!isnormal(nearClip)) nearClip = 0.01f;
    if (!isnormal(aspectRatio)) aspectRatio = 16.0f/9.0f;
    if (!isnormal(horizontalFOV)) horizontalFOV = M_PI * 0.3f;

    verticalFOV = horizontalFOV / aspectRatio;
}
