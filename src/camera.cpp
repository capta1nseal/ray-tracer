#include "camera.hpp"


#include "raymath/raymath.hpp"


#include <math.h>


Camera::Camera(
    const Vec3& initPosition, const Orientation& initOrientation,
    unsigned int initWidth, unsigned int initHeight,
    float initHorizontalFOV
)
{
    // quick sanity check on inputs
    if (initWidth == 0) initWidth = 1;
    if (initHeight == 0) initHeight = 1;

    if (!isnormal(initHorizontalFOV)) initHorizontalFOV = 55.0 * M_PI / 180.0;

    position = initPosition;
    orientation = initOrientation;
    
    width = initWidth;
    height = initHeight;

    aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    horizontalFOV = initHorizontalFOV;
    verticalFOV = horizontalFOV / aspectRatio;

    targetPlane = getTargetPlane();
}

Plane Camera::getTargetPlane()
{
    float toPlane = 1.0f;
    float toLeft = toPlane * tan(horizontalFOV / 2.0f);
    float toBottom = toLeft / aspectRatio;
    float planeWidth = 2.0f * toPlane * tan(horizontalFOV / 2.0f);
    float planeHeight = planeWidth / aspectRatio;

    float distanceToEdge = sqrt(toPlane * toPlane + toLeft * toLeft);
    float distanceToCorner = sqrt(toPlane * toPlane + toLeft * toLeft + toBottom * toBottom);

    float cornerAltitude = abs(
        acos(
            (distanceToCorner * distanceToCorner + distanceToEdge * distanceToEdge - toBottom * toBottom) / (2 * distanceToCorner * distanceToEdge)
        )
    );
    Direction toCorner = Direction(orientation.yaw - horizontalFOV / 2.0f, orientation.pitch - cornerAltitude);

    Vec3 corner = position + Vec3(toCorner) * distanceToCorner;

    Vec3 upVec = Vec3(Direction(orientation.yaw, orientation.pitch + M_PI / 2.0f));
    Vec3 rightVec = Vec3(Direction(orientation.yaw + M_PI / 2.0f, orientation.pitch));

    return Plane(corner, upVec * planeHeight, rightVec * planeWidth);
}
