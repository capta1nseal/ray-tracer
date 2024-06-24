#include "raytracer.hpp"


#include <random>

#include "frame.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "geometry/primitiveintersector.hpp"
#include "raymath/raymath.hpp"
#include "material.hpp"


RayTracer::RayTracer(Scene& initScene, Camera<double>& initCamera)
    : camera(initCamera),
    frame(initCamera.getWidth(), initCamera.getHeight()),
    scene(initScene),
    randomEngine(std::random_device{}()),
    unitDistribution(0.0, 1.0), trigDistribution(-1.0, 1.0), angleDistribution(-pi, pi)
{
    sampleCount = 0;
    maxSamples = 4096;
    maxBounces = 12;
}

void RayTracer::setCamera(Camera<double>& newCamera)
{
    camera = newCamera;
    frame = Frame(camera.getWidth(), camera.getHeight());
    sampleCount = 0;
}

void RayTracer::setMaxSamples(unsigned int newMaxSamples)
{
    maxSamples = newMaxSamples;
}

void RayTracer::sampleFrame()
{
    sampleCount++;

    Ray<double> cameraRay;
    HitInfo<double> hitInfo;
    HitInfo<double> nearestHitInfo;


    unsigned int width = frame.getWidth();
    unsigned int height = frame.getHeight();

    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            cameraRay = camera.getRayToSubPixel(x + unitDistribution(randomEngine), y + unitDistribution(randomEngine));

            frame.addSample(x, y, traceRay(cameraRay, maxBounces));
        }
    }
}

Vec3<double> RayTracer::traceRay(Ray<double> ray, unsigned int depthLeft)
{
    HitInfo<double> hitInfo, nearestHitInfo = {};

    for (const auto& primitiveObject : scene.getPrimitiveObjects())
    {
        hitInfo = std::visit(primitiveIntersector.with(&ray), primitiveObject.getPrimitive());

        if (hitInfo.didHit)
        {
            if (nearestHitInfo.didHit == false or hitInfo.distance < nearestHitInfo.distance)
            {
                nearestHitInfo = hitInfo;
                nearestHitInfo.material = primitiveObject.getMaterial();
            }
        }
    }

    if (nearestHitInfo.didHit)
    {
        Vec3<double> emittedLight = nearestHitInfo.material.emissionColor * nearestHitInfo.material.emissionStrength;

        if (depthLeft == 0u) return emittedLight;

        bool isSpecularBounce = nearestHitInfo.material.specularProbability >= unitDistribution(randomEngine);

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

Vec3<double> RayTracer::bounceDirection(const Vec3<double>& incomingRay, const Vec3<double>& normal, bool isSpecularBounce, double materialSmoothness)
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

Vec3<double> RayTracer::getRandomUniformDirectionSphere()
{
    return Orientation<double>(
        0.0,
        std::asin(trigDistribution(randomEngine)),
        angleDistribution(randomEngine)
    ).forward();
}
Vec3<double> RayTracer::getRandomUniformDirectionHemisphere(const Vec3<double>& normal)
{
    Vec3<double> direction = getRandomUniformDirectionSphere();
    return (normal * direction < 0.0) ? -direction : direction;
}
Vec3<double> RayTracer::getRandomBiasedDirectionHemisphere(const Vec3<double>& normal)
{
    return (getRandomUniformDirectionSphere() + normal).normalized();
}
