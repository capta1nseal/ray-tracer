#include "camera.hpp"


#include <math.h>

#include "raymath/raymath.hpp"


Camera::Camera(
    const Vec3& initPosition, const Orientation& initOrientation,
    unsigned int initWidth, unsigned int initHeight,
    float initHorizontalFOV
)
{
    // quick sanity check on inputs
    if (initWidth == 0) initWidth = 1;
    if (initHeight == 0) initHeight = 1;

    if (!isnormal(initHorizontalFOV)) initHorizontalFOV = 49.0 * M_PI / 180.0;

    position = initPosition;
    orientation = initOrientation;
    
    width = initWidth;
    height = initHeight;

    aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    horizontalFOV = initHorizontalFOV;
    verticalFOV = horizontalFOV / aspectRatio;

    targetPlane = getTargetPlane();
}

float Camera::getWidth() const {return width;}
float Camera::getHeight() const {return height;}

Plane Camera::getTargetPlane() const
{
    float toPlane = 1.0f;
    float toLeft = toPlane * tan(horizontalFOV / 2.0f);
    float toBottom = toLeft / aspectRatio;

    Vec3 forwardVec = Vec3(orientation);
    Vec3 upVec = Vec3(Direction(orientation.yaw, orientation.pitch + M_PI / 2.0f));
    Vec3 rightVec = upVec % forwardVec;
    // right direction would require an actual 3D rotation transform to calculate without cross product

    Vec3 toCorner = forwardVec * toPlane + rightVec * -1 * toLeft + upVec * -1 * toBottom;

    Vec3 corner = position + toCorner;
    Vec3 edgeX = rightVec * toLeft * 2.0f;
    Vec3 edgeY = upVec * toBottom * 2.0f;

    return Plane(corner, edgeX, edgeY);
}

Ray Camera::getRayToPixel(unsigned int x, unsigned int y) const
{
    auto target = targetPlane.corner + targetPlane.edge1 * ((static_cast<float>(x) + 0.5f) / static_cast<float>(width)) + targetPlane.edge2 * ((static_cast<float>(y) + 0.5f) / static_cast<float>(height));
    auto toTarget = target - position;
    return Ray(position, toTarget);
}
