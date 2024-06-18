#include "camera.hpp"


#include <cmath>

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

    if (!std::isnormal(initHorizontalFOV) or initHorizontalFOV <= 0.0f) initHorizontalFOV = 49.0f*M_PI/180.0f;

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

    Vec3 forwardVec = orientation.forward();
    Vec3 upVec = orientation.up();
    Vec3 rightVec = upVec % forwardVec;
    // right direction would require an actual 3D rotation transform to calculate without cross product

    Vec3 toCorner = forwardVec * toPlane + rightVec * -1 * toLeft + upVec * -1 * toBottom;

    Vec3 corner = position + toCorner;
    Vec3 edgeX = rightVec * toLeft * 2.0f;
    Vec3 edgeY = upVec * toBottom * 2.0f;

    return Plane(corner, edgeX, edgeY);
}

Ray Camera::getRayToPixel(float x, float y) const
{
    Vec3 target = targetPlane.corner + targetPlane.edge1 * ((x + 0.5f) / static_cast<float>(width)) + targetPlane.edge2 * ((y + 0.5f) / static_cast<float>(height));
    return Ray(position, target - position);
}
