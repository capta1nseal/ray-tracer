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

        auto camera = Camera(
            Vec3(-16.0, 7.5, 4.0),
            Orientation( M_PI * 0.0, M_PI * -0.07, M_PI * -0.15),
            16 * 7, 9 * 7
        );

        PrimitiveIntersector intersector;
        
        Ray ray;
        HitInfo hitInfo;

        for (unsigned int y = camera.getHeight(); y > 0; y--)
        {
            for (unsigned int x = 0; x < camera.getWidth(); x++)
            {
                bool anyIntersection = false;
                HitInfo nearestHitInfo;
                for (const auto& primitive : world.getPrimitives())
                {
                    ray = camera.getRayToPixel(x, y);
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
                    float valueOfInterest = nearestHitInfo.normal.x;
                    if (valueOfInterest < 0.0f) std::cout << "-";
                    else if (valueOfInterest > 0.0f) std::cout << "+";
                    else std::cout << "0";

                    valueOfInterest = nearestHitInfo.normal.y;
                    if (valueOfInterest < 0.0f) std::cout << "-";
                    else if (valueOfInterest > 0.0f) std::cout << "+";
                    else std::cout << "0";
                }
                else std::cout << "  ";
            }
            std::cout << "|\n";
        }

        if (frameCount >= 1) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(frameCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e7 << " ms\n";
}
