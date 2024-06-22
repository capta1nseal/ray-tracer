#include "application.hpp"


#include <chrono>
#include <iostream>
#include <random>

#include "camera.hpp"
#include "scene.hpp"
#include "geometry/geometry.hpp"
#include "material.hpp"
#include "frame.hpp"


RayTracerApplication::RayTracerApplication() {}

void RayTracerApplication::run()
{
    auto clock = std::chrono::steady_clock();
    auto start = clock.now();
    unsigned int sampleCount = 0;

    double terminalFontAspectRatio = 1.8;

    unsigned int terminalWidth = (16 * 8) * terminalFontAspectRatio;
    unsigned int terminalHeight = 9 * 8;

    Frame frame = Frame(terminalWidth, terminalHeight);

    Camera camera = Camera(
        Vec3(-17.0, 7.0, 10.0),
        Orientation( M_PI * 0.0, M_PI * -0.11, M_PI * 0.125),
        terminalWidth, terminalHeight,
        45.0 * M_PI / 180.0, terminalFontAspectRatio
    );

    PrimitiveIntersector<double> intersector;

    unsigned int maxSamples = 4096;

    unsigned int frameFrequency = 128;

    Vec3<double> skyEmissionColor = {0.5, 0.5, 1.0};
    double skyEmissionStrength = 1.0;

    double sunRadiusScale = 10.0;
    Vec3<double> sunEmissionColor = {0.9922, 0.9843, 0.8275};
    double sunEmissionStrength = 1.0e4 / (sunRadiusScale * sunRadiusScale);
    // Normalized direction vector pointing towards sun.
    Vec3<double> sunDirection = Vec3(-12.5, 35.0, 20.0).normalized();
    // Sun radius is its angular radius in rad.
    double sunRadius = 0.5 * M_PI / 180.0 * sunRadiusScale;
    double cosSunRadius = std::cos(sunRadius);

    unsigned int maxBounces = 12;

    std::default_random_engine randomEngine{std::random_device{}()};
    std::uniform_real_distribution<double> unitDistribution(0.0, 1.0);
    std::uniform_real_distribution<double> trigDistribution(-1.0, 1.0);
    std::uniform_real_distribution<double> angleDistribution(-pi, pi);

    start = clock.now();

    bool running = true;
    while (running)
    {
        sampleCount++;


        for (int y = 0; y < terminalHeight; y++)
        {
            for (unsigned int x = 0; x < terminalWidth; x++)
            {
                Ray<double> cameraRay = camera.getRandomRayToPixel(x, y);
                Ray<double> ray = cameraRay;
                bool anyIntersection = false;
                HitInfo<double> hitInfo;
                HitInfo<double> nearestHitInfo;

                Vec3<double> rayColor = {1.0, 1.0, 1.0};
                Vec3<double> incomingLight = {0.0, 0.0, 0.0};

                for (unsigned int currentBounce = 0; currentBounce <= maxBounces; currentBounce++)
                {
                    anyIntersection = false;
                    nearestHitInfo = HitInfo<double>();
                    for (const auto& primitiveObject : scene.getPrimitiveObjects())
                    {
                        hitInfo = std::visit(intersector.with(&ray), primitiveObject.getPrimitive());

                        if (hitInfo.didHit)
                        {
                            hitInfo.material = primitiveObject.getMaterial();
                            anyIntersection = true;
                            if (nearestHitInfo.didHit == false or hitInfo.distance < nearestHitInfo.distance)
                            {
                                nearestHitInfo = hitInfo;
                            }
                        }
                    }

                    // The following applies the current material model to the ray colour and incoming light.
                    if (anyIntersection)
                    {
                        bool isSpecularBounce = nearestHitInfo.material.specularProbability >= unitDistribution(randomEngine);
                        // Randomly generated direction of diffuse bounce.
                        // This generates a normalized vector in a uniform spherical distribution 
                        // then converts it to a hemispherical biased distribution 
                        // in a relatively cheap manner.
                        // The bias perfectly accounts for lower angles compared to the surface normal contributing less light.
                        Vec3 diffuseDir = (nearestHitInfo.normal + Orientation(
                            0.0,
                            std::asin(trigDistribution(randomEngine)),
                            angleDistribution(randomEngine)
                        ).forward()).normalized();
                        // Perfect specular reflection is easy.
                        Vec3 specularDir = ray.direction.reflected(nearestHitInfo.normal);
                        // Emission is considered to be equal in all directions.
                        Vec3 emittedLight = nearestHitInfo.material.emissionColor * nearestHitInfo.material.emissionStrength;
                        incomingLight += multiplyElements(emittedLight, rayColor);
                        rayColor *= lerp(nearestHitInfo.material.color, nearestHitInfo.material.specularColor, isSpecularBounce);
                        // Exit early if dot product of all bounce colours is too low to matter.
                        if (sumElements(rayColor) < 1.0e-4) break;
                        ray.direction = lerp(diffuseDir, specularDir, nearestHitInfo.material.smoothness * isSpecularBounce).normalized();
                        // Ray origin offset to eliminate self-intersection.
                        // TODO implement a better way to ignore intersections within ~0 distance of ray origin.
                        // Currently hard-coded in primitives.
                        ray.origin = nearestHitInfo.hitPoint;
                    }
                    else
                    {
                        double skyRayElevation = (ray.direction.z + 1.0) / 2.0;
                        double skyFactor = skyRayElevation * skyRayElevation;
                        Vec3<double> emittedLight = skyEmissionColor * skyEmissionStrength * skyFactor;

                        if (ray.direction * sunDirection > cosSunRadius)
                        {
                            emittedLight += sunEmissionColor * sunEmissionStrength;
                        }

                        incomingLight += multiplyElements(emittedLight, rayColor);
                        break;
                    }
                }

                Vec3<double> newFrameColor = incomingLight;
                frame.addSample(x, y, newFrameColor);
            }
        }

        if ((sampleCount - 1) % frameFrequency == 0 or sampleCount == maxSamples) std::cout << frame;
        
        if (sampleCount >= maxSamples) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(sampleCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e6 << " ms\n";
}
