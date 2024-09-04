#include "raytracer.hpp"


#include <random>
#include <memory>
#include <thread>

#include "frame.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "raymath/raymath.hpp"
#include "material.hpp"
#include "randomgenerator.hpp"
#include "workqueue.hpp"


RayTracer::RayTracer(Scene& initScene, Camera& initCamera, const std::shared_ptr<RandomGenerator>& prandomGenerator)
    : camera(initCamera),
    frame(initCamera.getWidth(), initCamera.getHeight()),
    scene(initScene),
    randomGenerator(prandomGenerator)
{
    sampleCount = 0;
    maxSamples = 4096;
    maxBounces = 12;
}

void RayTracer::setCamera(Camera& newCamera)
{
    camera = newCamera;
    frame = Frame(camera.getWidth(), camera.getHeight());
    sampleCount = 0;
}

void RayTracer::setMaxSamples(unsigned int newMaxSamples)
{
    maxSamples = newMaxSamples;
}

void RayTracer::rowSampler(WorkQueue* workQueue)
{
    int y = workQueue->getTask();

    unsigned int width = frame.getWidth();

    std::vector<Vec3<double>> rowValues(width, Vec3(0.0,0.0,0.0));

    while (y != -1)
    {
        for (unsigned int x = 0; x < width; x++)
        {
            frame.addSample(
                x, y,
                traceRay(
                    camera.getRandomRayToPixel(x, y),
                    maxBounces
                )
            );
        }

        y = workQueue->getTask();
    }

    return;
}

void RayTracer::sampleFrame()
{
    sampleCount++;

    Ray cameraRay;
    HitInfo hitInfo;
    HitInfo nearestHitInfo;


    unsigned int width = frame.getWidth();
    unsigned int height = frame.getHeight();

    WorkQueue workQueue = WorkQueue();

    workQueue.queueTasks(height);

    std::vector<std::thread> threads;

    unsigned int threadCount = std::thread::hardware_concurrency();

    for (unsigned int i = 0u; i < threadCount; i++)
    {
        threads.push_back(std::thread(&RayTracer::rowSampler, this, &workQueue));
    }

    for (unsigned int i = 0u; i < threadCount; i++)
    {
        threads[i].join();
    }

    //for (unsigned int x = 0; x < width; x++)
    //{
    //    for (unsigned int y = 0; y < height; y++)
    //    {
    //        cameraRay = camera.getRayToSubPixel(x + randomGenerator->randomLinearUnit(), y + randomGenerator->randomLinearUnit());
    //
    //        frame.addSample(x, y, traceRay(cameraRay, maxBounces));
    //    }
    //}
}

Vec3<double> RayTracer::traceRay(Ray ray, unsigned int depthLeft) const
{
    HitInfo hitInfo, nearestHitInfo = {};

    for (const auto& primitiveObject : scene.getPrimitiveObjects())
    {
        hitInfo = primitiveObject.primitive->intersectRay(ray);

        if (hitInfo.didHit)
        {
            if (nearestHitInfo.didHit == false or hitInfo.distance < nearestHitInfo.distance)
            {
                nearestHitInfo = hitInfo;
                nearestHitInfo.material = primitiveObject.material;
            }
        }
    }

    if (nearestHitInfo.didHit)
    {
        Vec3<double> emittedLight = nearestHitInfo.material.emissionColor * nearestHitInfo.material.emissionStrength;

        if (depthLeft == 0u) return emittedLight;

        bool isSpecularBounce = nearestHitInfo.material.specularProbability >= randomGenerator->randomLinearUnit();

        return emittedLight + multiplyElements(
            traceRay(
                Ray(
                    nearestHitInfo.hitPoint,
                    bounceDirection(ray.direction, nearestHitInfo.normal, isSpecularBounce, nearestHitInfo.material.smoothness)
                ),
                depthLeft - 1
            ),
            isSpecularBounce ? nearestHitInfo.material.specularColor : nearestHitInfo.material.color
        );
    }
    else
    {
        return scene.getEnvironmentEmission(ray.direction);
    }
}

Vec3<double> RayTracer::bounceDirection(const Vec3<double>& incomingRay, const Vec3<double>& normal, bool isSpecularBounce, double materialSmoothness) const
{
    Vec3<double> diffuseDirection = getRandomBiasedDirectionHemisphere(normal);
    // If the reflection is determined to not be specular, just return diffuse direction.
    if (!isSpecularBounce) return diffuseDirection;
    // TODO find out exactly what this simulates, why and how it lines up with reality.
    return lerp(diffuseDirection, reflect(incomingRay, normal), materialSmoothness).normalized();
}


const unsigned int& RayTracer::getSampleCount() const
{
    return sampleCount;
}
const unsigned int& RayTracer::getMaxSamples() const
{
    return maxSamples;
}

const Frame& RayTracer::getFrame() const
{
    return frame;
}

Vec3<double> RayTracer::getRandomUniformDirectionSphere() const
{
    return Orientation<double>(
        0.0,
        std::asin(randomGenerator->randomLinearTrig()),
        randomGenerator->randomLinearAngle()
    ).forward();
}
Vec3<double> RayTracer::getRandomUniformDirectionHemisphere(const Vec3<double>& normal) const
{
    Vec3<double> direction = getRandomUniformDirectionSphere();
    return (normal * direction < 0.0) ? -direction : direction;
}
Vec3<double> RayTracer::getRandomBiasedDirectionHemisphere(const Vec3<double>& normal) const
{
    return (getRandomUniformDirectionSphere() + normal).normalized();
}
