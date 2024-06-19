#include "application.hpp"


#include <chrono>
#include <iostream>

#include "world.hpp"
#include "geometry/geometry.hpp"
#include "camera.hpp"


RayTracerApplication::RayTracerApplication()
{   
}

void RayTracerApplication::run()
{
    auto clock = std::chrono::steady_clock();
    auto start = clock.now();
    unsigned int frameCount = 0;

    bool running = true;
    while (running)
    {
        frameCount++;

        Camera camera = Camera(
            Vec3(-16.0, 6.0, 2.0),
            Orientation( M_PI * 0.0, M_PI * 0.04, M_PI * -0.125),
            16 * 8, 9 * 8,
            49.0 * M_PI / 180.0
        );

        Vec3<double> light{-6, 8, 10};

        PrimitiveIntersector<double> intersector;
        
        Ray<double> ray;
        HitInfo<double> hitInfo;

        double terminalFontAspectRatio = 1.8;

        unsigned int terminalWidth = camera.getWidth() * terminalFontAspectRatio;

        for (unsigned int y = camera.getHeight(); y > 0; y--)
        {
            for (unsigned int x = 0; x < terminalWidth; x++)
            {
                bool anyIntersection = false;
                HitInfo<double> nearestHitInfo;
                for (const auto& primitive : world.getPrimitives())
                {
                    ray = camera.getRayToPixel(x / terminalFontAspectRatio, y);
                    hitInfo = std::visit(intersector.with(&ray), primitive);
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
                    double ambientIntensity = 0.05;
                    double diffuseIntensity = 1.0;
                    double specularIntensity = 2.0;
                    double roughness = 0.45;
                    double specularPower = 2.0 / (roughness * roughness) - 2.0;

                    auto location = nearestHitInfo.hitPoint;
                    auto toCamera = (camera.getPosition() - location).normalized();
                    auto toLight = (light - location).normalized();

                    auto ambient = ambientIntensity;
                    auto diffuse = diffuseIntensity * std::clamp(nearestHitInfo.normal * toLight, 0.0, 1.0);
                    auto specular = specularIntensity * std::pow(std::clamp(toLight.reflected(nearestHitInfo.normal) * toCamera, 0.0, 1.0), specularPower);

                    auto lightLevel = ambient;

                    bool anyOcclusion = false;
                    for (const auto& primitive : world.getPrimitives())
                    {
                        ray = Ray(location + 0.0001 * toLight, toLight);
                        hitInfo = std::visit(intersector.with(&ray), primitive);
                        if (hitInfo.didHit)
                        {
                            anyOcclusion = true;
                        }
                    }
                    if (!anyOcclusion) lightLevel += diffuse + specular;


                    double gamma = 1.0;
                    lightLevel = std::pow(lightLevel, 1.0 / gamma);


                    unsigned int nearestOpacityIndex = 0;
                    double nearestOpacityDifference = 2.0;

                    std::vector<double> opacityValues{0.0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417, 0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747, 0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382, 0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881, 0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972, 0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039, 0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999};

                    for (unsigned int i = opacityValues.size() - 1; i != 0; i--)
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
                else std::cout << " ";
            }
            std::cout << "|\n";
        }

        if (frameCount >= 1) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(frameCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e7 << " ms\n";
}
