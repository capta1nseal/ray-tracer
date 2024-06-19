#include "application.hpp"


#include <chrono>
#include <iostream>
#include <random>

#include "camera.hpp"
#include "world.hpp"
#include "geometry/geometry.hpp"
#include "material.hpp"
#include "frame.hpp"


RayTracerApplication::RayTracerApplication()
{
    // std::cout << std::ios_base::sync_with_stdio(false) << "\n";
}

void RayTracerApplication::run()
{
    auto clock = std::chrono::steady_clock();
    auto start = clock.now();
    unsigned int sampleCount = 0;

    double terminalFontAspectRatio = 1.8;

    unsigned int terminalWidth = (16 * 13) * terminalFontAspectRatio;
    unsigned int terminalHeight = 9 * 13;

    Frame frame = Frame(terminalWidth, terminalHeight);

    Camera camera = Camera(
        Vec3(-20.0, 8.0, 9.0),
        Orientation( M_PI * 0.0, M_PI * 0.07, M_PI * -0.125),
        terminalWidth, terminalHeight,
        49.0 * M_PI / 180.0, terminalFontAspectRatio
    );

    PrimitiveIntersector<double> intersector;

    unsigned int maximumSamples = 4096;

    unsigned int frameFrequency = 128;
    
    double gamma = 1.0;

    Material material = {
        {0.7, 0.7, 0.7},
        {0.9, 0.9, 0.9},
        {1.0, 1.0, 1.0},
        0.3,
        0.9,
        0.0
    };
    Material lightMaterial = {
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {1.0, 1.0, 1.0},
        0.0,
        0.0,
        250.0
    };

    Vec3 environmentEmissionColor = {1.0, 1.0, 1.0};
    double environmentEmissionStrength = 0.0;

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


        for (int y = terminalHeight; y > -1; y--)
        {
            for (unsigned int x = 0; x < terminalWidth; x++)
            {
                Ray<double> cameraRay = camera.getRandomRayToPixel(x, y);
                Ray<double> finalRay = cameraRay;
                Ray<double> ray;
                bool anyIntersection = false;
                HitInfo<double> hitInfo;
                HitInfo<double> nearestHitInfo;

                Vec3<double> rayColor = {1.0, 1.0, 1.0};
                Vec3<double> incomingLight = {0.0, 0.0, 0.0};

                for (unsigned int currentBounce = 0; currentBounce <= maxBounces; currentBounce++)
                {
                    ray = finalRay;
                    anyIntersection = false;
                    nearestHitInfo = HitInfo<double>();
                    for (const auto& primitive : world.getPrimitives())
                    {
                        hitInfo = std::visit(intersector.with(&ray), primitive);
                        hitInfo.material = material;

                        if (hitInfo.didHit)
                        {
                            anyIntersection = true;
                            if (nearestHitInfo.didHit == false or hitInfo.distance < nearestHitInfo.distance)
                            {
                                nearestHitInfo = hitInfo;
                            }
                        }
                    }

                    std::vector<Primitive<double>> lights;
                    lights.push_back(Sphere<double>(
                        Vec3<double>(-3, -13, 20),
                        1.5
                    ));
                    lights.push_back(Sphere<double>(
                        Vec3<double>( 0, 3, 5.5),
                        0.1
                    ));
                    lights.push_back(Sphere<double>(
                        Vec3<double>( 0,-3, 5.5),
                        0.1
                    ));
                    lights.push_back(Sphere<double>(
                        Vec3<double>(-3, 0, 5.5),
                        0.1
                    ));
                    lights.push_back(Sphere<double>(
                        Vec3<double>(-3, 0, 5.5),
                        0.1
                    ));

                    for (const auto& lightPlane : lights)
                    {
                        hitInfo = std::visit(intersector.with(&ray), lightPlane);
                        hitInfo.material = lightMaterial;

                        if (hitInfo.didHit)
                        {
                            anyIntersection = true;
                            if (nearestHitInfo.didHit == false or hitInfo.distance < nearestHitInfo.distance)
                            {
                                nearestHitInfo = hitInfo;
                            }
                        }
                    }

                    if (anyIntersection)
                    {
                        bool isSpecularBounce = nearestHitInfo.material.specularProbability >= unitDistribution(randomEngine);
                        // Randomly generated direction of diffuse bounce.
                        // This mess generates a normalized vector in a spherical distribution 
                        // then converts it to a hemispherical normal distribution
                        // in a relatively cheap manner.
                        Vec3 diffuseDir = (nearestHitInfo.normal + Orientation(
                            0.0,
                            std::asin(trigDistribution(randomEngine)),
                            angleDistribution(randomEngine)
                        ).forward()).normalized();
                        Vec3 specularDir = finalRay.direction.reflected(nearestHitInfo.normal);
                        finalRay.direction = lerp(diffuseDir, specularDir, nearestHitInfo.material.smoothness * isSpecularBounce).normalized();
                        Vec3 emittedLight = nearestHitInfo.material.emissionColor * nearestHitInfo.material.emissionStrength;
                        incomingLight += emittedLight *= rayColor;
                        rayColor *= lerp(nearestHitInfo.material.color, nearestHitInfo.material.specularColor, isSpecularBounce);
                        finalRay.origin = nearestHitInfo.hitPoint;
                    }
                    else
                    {
                        Vec3 emittedLight = environmentEmissionColor * environmentEmissionStrength;
                        incomingLight += emittedLight *= rayColor;
                        break;
                    }
                }

                // Value is clamped loosely to still get correct averages at high-contrast pixels, but ignore anomalies if they occur.
                Vec3<double> newFrameColor = clamp(incomingLight, 0.0, 1000.0);;
                if (finalRay.origin == cameraRay.origin and finalRay.direction == cameraRay.direction) newFrameColor = Vec3<double>(0.0, 0.0, 0.0);
                frame.add(x, y, newFrameColor);

                if ((sampleCount - 1) % frameFrequency == 0)
                {
                    Vec3<double> accumulatedColor = frame.at(x, y);
                    
                    double lightLevel = std::clamp(accumulatedColor.x, 0.0, 1.0);

                    lightLevel = std::pow(lightLevel, 1.0 / gamma);

                    unsigned int nearestOpacityIndex = 0;
                    double nearestOpacityDifference = 2.0;

                    std::vector<double> opacityValues{0.0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417, 0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747, 0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382, 0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881, 0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972, 0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039, 0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999};

                    for (int i = opacityValues.size() - 1; i > -1; i--)
                    {
                        double difference = std::abs(lightLevel - opacityValues[i]);
                        if (difference < nearestOpacityDifference)
                        {
                            nearestOpacityDifference = difference;
                            nearestOpacityIndex = i;
                        }
                    }

                    std::cout << " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@"[nearestOpacityIndex];
                }
            }
            if ((sampleCount - 1) % frameFrequency == 0) std::cout << "|\n";

        }
        
        if (sampleCount >= maximumSamples) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(sampleCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e6 << " ms\n";
}
