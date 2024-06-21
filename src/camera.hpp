#ifndef _RAYTRACERCAMERA_
#define _RAYTRACERCAMERA_


#include <cmath>
#include <random>

#include "raymath/raymath.hpp"
#include "geometry/primitives/plane.hpp"


/*
Wrapper for camera's spatial positioning and lens values.
Creates a plane upon initialization that makes projecting rays very easy.
relativePixelHeight parameter is intended to be used only when pixels are non-square rectangles.
*/
template<Vec3Basis T>
class Camera
{
public:
    Camera(
        const Vec3<T>& initPosition = {}, const Orientation<T>& initOrientation = {},
        unsigned int initWidth = 1920, unsigned int initHeight = 1080,
        T initHorizontalFOV = {49.0*M_PI/180.0}, T relativePixelHeight = T(1.0)
    )
    {
        // quick sanity check on inputs
        if (initWidth == 0) initWidth = 1;
        if (initHeight == 0) initHeight = 1;

        if (!std::isnormal(initHorizontalFOV) or initHorizontalFOV <= T(0.0)) initHorizontalFOV = 49.0*M_PI/180.0;
        if (!std::isnormal(relativePixelHeight) or relativePixelHeight <= T(0.0)) relativePixelHeight = T(1.0);

        position = initPosition;
        orientation = initOrientation;
        
        width = initWidth;
        height = initHeight;

        aspectRatio = T(width) / (T(height) * relativePixelHeight);

        horizontalFOV = initHorizontalFOV;
        verticalFOV = initHorizontalFOV / aspectRatio;

        targetPlaneSet = false;
        targetPlane = getTargetPlane();
        targetPlaneSet = true;

        std::random_device randomDevice;
        gen.seed(randomDevice());
        subPixelDistribution = std::uniform_real_distribution<T>(0.0, 1.0);
    }
    template<Vec3Basis U> Camera(const Camera<U>& other)
        : position(other.position), orientation(other.orientation),
        width(other.width), height(other.height),
        aspectRatio(other.aspectRatio), horizontalFOV(other.horizontalFOV), verticalFOV(other.verticalFOV)
        {}

    const Vec3<T>& getPosition() const { return position; }
    const Orientation<T>& getOrientation() const { return orientation; }

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }

    Plane<T> getTargetPlane() const
    {
        if (targetPlaneSet) return targetPlane;

        T toPlane = 1.0;
        T toLeft = toPlane * std::tan(horizontalFOV * 0.5);
        T toBottom = toLeft / aspectRatio;

        Vec3<T> forwardVec = orientation.forward();
        Vec3<T> upVec = orientation.up();
        Vec3<T> rightVec = forwardVec % upVec;

        Vec3<T> toCorner = forwardVec * toPlane + rightVec * -toLeft + upVec * -toBottom;

        Vec3<T> corner = position + toCorner;
        Vec3<T> edgeX = rightVec * toLeft * 2.0;
        Vec3<T> edgeY = upVec * toBottom * 2.0;

        return Plane<T>(corner, edgeX, edgeY);
    }

    // Get a ray from camera position pointing towards the center of pixel (x, y) within the set resolution.

    Ray<T> getRayToPixel(unsigned int x, unsigned int y) const
    {
        return getRayToSubPixel(
            (T(x) + T(0.5)) / T(width),
            (T(y) + T(0.5)) / T(height)
        );
    }
    // Get a ray from camera position pointing towards a raydom sub-pixel position within the given pixel.
    // The pixel is defined according to the constructed target plane, width and height.
    Ray<T> getRandomRayToPixel(unsigned int x, unsigned int y)
    {
        return getRayToSubPixel(
            (T(x) + subPixelDistribution(gen)) / T(width),
            (T(y) + subPixelDistribution(gen)) / T(height)
        );
    }
    // Get a ray from camera position pointing towards a sub-pixel position:
    // (x * width, y * height) within the target plane.
    Ray<T> getRayToSubPixel(T x, T y) const
    {
        return {
            position,
            ((targetPlane.corner - position) + targetPlane.edge1 * x + targetPlane.edge2 * y).normalized()
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
    bool targetPlaneSet;
    Plane<T> targetPlane;

    std::mt19937 gen;
    std::uniform_real_distribution<T> subPixelDistribution;
};


#endif
