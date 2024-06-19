#ifndef _RAYTRACERCAMERA_
#define _RAYTRACERCAMERA_


#include <cmath>

#include "raymath/raymath.hpp"
#include "geometry/primitives/plane.hpp"


/*
Wrapper for camera's spatial positioning and lens values.
Creates a plane upon initialization that makes projecting rays very easy.
*/
template<Vec3Basis T>
class Camera
{
public:
    Camera(
        const Vec3<T>& initPosition = {}, const Orientation<T>& initOrientation = {},
        unsigned int initWidth = 1920, unsigned int initHeight = 1080,
        T initHorizontalFOV = {49.0*M_PI/180.0}
    )
    {
        // quick sanity check on inputs
        if (initWidth == 0) initWidth = 1;
        if (initHeight == 0) initHeight = 1;

        if (!std::isnormal(initHorizontalFOV) or initHorizontalFOV <= 0.0f) initHorizontalFOV = 49.0*M_PI/180.0;

        position = initPosition;
        orientation = initOrientation;
        
        width = initWidth;
        height = initHeight;

        aspectRatio = T(width) / T(height);

        horizontalFOV = initHorizontalFOV;
        verticalFOV = horizontalFOV / aspectRatio;

        targetPlane = getTargetPlane();
    }
    template<Vec3Basis U> Camera(const Camera<U>& other)
        : position(other.position), orientation(other.orientation),
        width(other.width), height(other.height),
        aspectRatio(other.aspectRatio), horizontalFOV(other.horizontalFOV), verticalFOV(other.verticalFOV)
        {}

    const Vec3<T>& getPosition() const { return position; }
    const Orientation<T>& getOrientation() const { return orientation; }

    T getWidth() const { return width; }
    T getHeight() const { return height; }

    Plane<T> getTargetPlane() const
    {
        T toPlane = 1.0;
        T toLeft = toPlane * std::tan(horizontalFOV * 0.5);
        T toBottom = toLeft / aspectRatio;

        Vec3<T> forwardVec = orientation.forward();
        Vec3<T> upVec = orientation.up();
        Vec3<T> rightVec = upVec % forwardVec;

        Vec3<T> toCorner = forwardVec * toPlane + rightVec * -toLeft + upVec * -toBottom;

        Vec3<T> corner = position + toCorner;
        Vec3<T> edgeX = rightVec * toLeft * 2.0;
        Vec3<T> edgeY = upVec * toBottom * 2.0;

        return Plane<T>(corner, edgeX, edgeY);
    }

    Ray<T> getRayToPixel(T x, T y) const
    {
        Vec3<T> target = targetPlane.corner + targetPlane.edge1 * ((x + 0.5) / T(width)) + targetPlane.edge2 * ((y + 0.5) / T(height));
        return {
            position,
            (target - position).normalized()
        };
    }

private:
    Vec3<T> position;
    Orientation<T> orientation;

    // lengths in m
    // angles in rad

    unsigned int width;
    unsigned int height;
    T aspectRatio;
    T horizontalFOV;
    T verticalFOV;

    // rays will be cast towards this plane, centered exactly 1 m in front of the camera.
    // the origin of the plane will be in the bottom left from the perspective of the camera.
    Plane<T> targetPlane;
};


#endif
