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

        Camera<float> camera = Camera<float>(
            Vec3(-16.0, 6.0, 2.0),
            Orientation( M_PI * 0.0f, M_PI * 0.04f, M_PI * -0.125f),
            16 * 13, 9 * 13,
            49.0 * M_PI / 180.0
        );

        PrimitiveIntersector<float> intersector;
        
        Ray<float> ray;
        HitInfo<float> hitInfo;

        float terminalFontAspectRatio = 1.8;

        for (unsigned int y = camera.getHeight(); y > 0; y--)
        {
            for (unsigned int x = 0; x < camera.getWidth() * terminalFontAspectRatio; x++)
            {
                bool anyIntersection = false;
                HitInfo<float> nearestHitInfo;
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
                    int opacityIndex = 0;
                    float valueOfInterest;

                    valueOfInterest = nearestHitInfo.normal.y;
                    if (valueOfInterest >= 0.0f) opacityIndex += 1;
                    if (valueOfInterest > 0.5f) opacityIndex += 1;

                    valueOfInterest = nearestHitInfo.normal.x;
                    if (valueOfInterest >= 0.0f) opacityIndex += 1;
                    if (valueOfInterest > 0.5f) opacityIndex += 1;

                    std::cout << "-+oIX"[opacityIndex];
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
