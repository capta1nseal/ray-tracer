#ifndef _RAYTRACERRAYTRACER_
#define _RAYTRACERRAYTRACER_


#include <random>
#include <memory>

#include "frame.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "raymath/raymath.hpp"
#include "material.hpp"
#include "randomgenerator.hpp"
#include "workqueue.hpp"


/*
Wrapper class for ray bouncing, sample generation and ray-traced rendering.
*/
class RayTracer
{
public:
    RayTracer(Scene& initScene, Camera& initCamera, const std::shared_ptr<RandomGenerator>& prandomGenerator);

    // Run whenever anything about camera changed, or the camera changes completely.
    void setCamera(Camera& newCamera);

    // Set new maximum number of samples per pixel.
    // Does not affect image generated, but may stop its render immediately if decreased.
    void setMaxSamples(unsigned int newMaxSamples);

    // For use with a WorkQueue, preferably multithreaded
    void rowSampler(WorkQueue* workQueue);

    // Generates at least one sample per pixel.
    // May generate additional samples through importance sampling.
    // Spawns multiple rowSampler threads that share a WorkQueue.
    void sampleFrame();

    // Sample incoming light from given ray's direction to its origin.
    // Will terminate path if depthLeft reaches 0.
    Vec3<double> traceRay(Ray ray, unsigned int depthLeft) const;

    // Generate outgoing ray direction based on incoming ray, surface normal and material properties.
    Vec3<double> bounceDirection(const Vec3<double>& incomingRay, const Vec3<double>& normal, bool isSpecularBounce, double materialSmoothness) const;

    const unsigned int& getSampleCount() const;
    const unsigned int& getMaxSamples() const;

    const Frame& getFrame() const;

    Vec3<double> getRandomUniformDirectionSphere() const;
    Vec3<double> getRandomUniformDirectionHemisphere(const Vec3<double>& normal) const;
    // Cosine-biased hemisphere distribution.
    // This means low-angle diffuse reflections don't need scaled down, instead they are just sampled less.
    Vec3<double> getRandomBiasedDirectionHemisphere(const Vec3<double>& normal) const;

private:
    unsigned int sampleCount, maxSamples, maxBounces;

    Camera& camera;
    Frame frame;

    Scene& scene;

    std::shared_ptr<RandomGenerator> randomGenerator;
};


#endif
