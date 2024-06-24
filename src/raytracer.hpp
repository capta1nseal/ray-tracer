#ifndef _RAYTRACERRAYTRACER_
#define _RAYTRACERRAYTRACER_


#include <random>

#include "frame.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "geometry/primitiveintersector.hpp"
#include "raymath/raymath.hpp"
#include "material.hpp"


/*
Wrapper class for ray bouncing, sample generation and ray-traced rendering.
*/
class RayTracer
{
public:
    RayTracer(Scene& initScene, Camera<double>& initCamera);

    // Run whenever anything about camera changed, or the camera changes completely.
    void setCamera(Camera<double>& newCamera);

    // Set new maximum number of samples per pixel.
    // Does not affect image generated, but may stop its render immediately if decreased.
    void setMaxSamples(unsigned int newMaxSamples);

    // Generates at least one sample per pixel.
    // May generate additional samples through importance sampling.
    void sampleFrame();

    // Sample incoming light from given ray's direction to its origin.
    // Will terminate path if depthLeft reaches 0.
    Vec3<double> traceRay(Ray<double> ray, unsigned int depthLeft);

    // Generate outgoing ray direction based on incoming ray, surface normal and material properties.
    Vec3<double> bounceDirection(const Vec3<double>& incomingRay, const Vec3<double>& normal, bool isSpecularBounce, double materialSmoothness);

    const unsigned int& getSampleCount() const;
    const unsigned int& getMaxSamples() const;

    const Frame& getFrame() const;

    Vec3<double> getRandomUniformDirectionSphere();
    Vec3<double> getRandomUniformDirectionHemisphere(const Vec3<double>& normal);
    // Cosine-biased hemisphere distribution.
    // This means low-angle diffuse reflections don't need scaled down, instead they are just sampled less.
    Vec3<double> getRandomBiasedDirectionHemisphere(const Vec3<double>& normal);

private:
    unsigned int sampleCount, maxSamples, maxBounces;

    Camera<double>& camera;
    Frame frame;

    Scene& scene;

    PrimitiveIntersector<double> primitiveIntersector;

    std::mt19937 randomEngine;
    std::uniform_real_distribution<double> unitDistribution;
    std::uniform_real_distribution<double> trigDistribution;
    std::uniform_real_distribution<double> angleDistribution;
};


#endif
