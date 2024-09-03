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
class Camera
{
public:
    Camera(
        const Vec3<double>& initPosition = {}, const Orientation<double>& initOrientation = {},
        unsigned int initWidth = 16, unsigned int initHeight = 9,
        double initHorizontalFOV = {49.0*M_PI/180.0}, double relativePixelHeight = 1.0
    )
    {
        if (initWidth == 0) initWidth = 1;
        if (initHeight == 0) initHeight = 1;

        if (!std::isnormal(initHorizontalFOV) or initHorizontalFOV <= 0.0) initHorizontalFOV = 49.0*M_PI/180.0;
        if (!std::isnormal(relativePixelHeight) or relativePixelHeight <= 0.0) relativePixelHeight = 1.0;

        position = initPosition;
        orientation = initOrientation;
        
        width = initWidth;
        height = initHeight;

        aspectRatio = double(width) / (double(height) * relativePixelHeight);

        horizontalFOV = initHorizontalFOV;
        verticalFOV = initHorizontalFOV / aspectRatio;

        targetPlaneSet = false;
        targetPlane = getTargetPlane();
        targetPlaneSet = true;

        std::random_device randomDevice;
        randomEngine.seed(randomDevice());
        subPixelDistribution = std::uniform_real_distribution<double>(0.0, 1.0);
    }
    template<Vec3Basis U> Camera(const Camera& other)
        : position(other.position), orientation(other.orientation),
        width(other.width), height(other.height),
        aspectRatio(other.aspectRatio), horizontalFOV(other.horizontalFOV), verticalFOV(other.verticalFOV)
        {}

    const Vec3<double>& getPosition() const { return position; }
    const Orientation<double>& getOrientation() const { return orientation; }

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }

    Plane getTargetPlane() const
    {
        if (targetPlaneSet) return targetPlane;

        double toPlane = 1.0;
        double toLeft = toPlane * std::tan(horizontalFOV * 0.5);
        double toBottom = toLeft / aspectRatio;

        Vec3<double> forwardVec = orientation.forward();
        Vec3<double> upVec = orientation.up();
        Vec3<double> rightVec = forwardVec % upVec;

        Vec3<double> toCorner = forwardVec * toPlane + rightVec * -toLeft + upVec * -toBottom;

        Vec3<double> corner = position + toCorner;
        Vec3<double> edgeX = rightVec * toLeft * 2.0;
        Vec3<double> edgeY = upVec * toBottom * 2.0;

        return Plane(corner, edgeX, edgeY);
    }

    // Get a ray from camera position pointing towards the center of pixel (x, y) within the set resolution.

    Ray getRayToPixel(unsigned int x, unsigned int y) const
    {
        return getRayToSubPixel(
            double(x) + 0.5,
            double(y) + 0.5
        );
    }
    // Get a ray from camera position pointing towards a raydom sub-pixel position within the given pixel.
    // The pixel is defined according to the constructed target plane, width and height.
    Ray getRandomRayToPixel(unsigned int x, unsigned int y)
    {
        return getRayToSubPixel(
            double(x) + subPixelDistribution(randomEngine),
            double(y) + subPixelDistribution(randomEngine)
        );
    }
    // Get a ray from camera position pointing towards a sub-pixel position:
    // (x * width, y * height) within the target plane.
    Ray getRayToSubPixel(double x, double y) const
    {
        return {
            position,
            ((targetPlane.corner - position) + targetPlane.edge1 * (x / double(width)) + targetPlane.edge2 * (y / double(height))).normalized()
        };
    }

private:
    Vec3<double> position;
    Orientation<double> orientation;

    // lengths in m
    // angles in rad

    unsigned int width;
    unsigned int height;
    double aspectRatio;
    double horizontalFOV;
    double verticalFOV;

    // rays will be cast towards this plane, centered exactly 1 m in front of the camera.
    // the origin of the plane will be in the bottom left from the perspective of the camera.
    bool targetPlaneSet;
    Plane targetPlane;

    std::mt19937 randomEngine;
    std::uniform_real_distribution<double> subPixelDistribution;
};


#endif
