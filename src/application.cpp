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
            Vec3(-10.0, 0.0, 0.0),
            Orientation( 0.0, 0.0, 0.0),
            16 * 7, 9 * 7
        );

        PrimitiveIntersector intersector;
        
        Ray ray;
        HitInfo hitInfo;

        for (unsigned int y = camera.getHeight(); y > 0; y--)
        {
            for (unsigned int x = 0; x < camera.getWidth(); x++)
            {
                bool intersection = false;
                for (const auto& primitive : world.getPrimitives())
                {
                    ray = camera.getRayToPixel(x, y);
                    hitInfo = std::visit(intersector.with(&ray), primitive);
                    if (hitInfo.didHit) intersection = true;
                }
                if (intersection) std::cout << "@@";
                else std::cout << "  ";
            }
            std::cout << "|\n";
        }

        if (frameCount >= 1) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(frameCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e7 << " ms\n";
}
