#include "application.hpp"


#include <chrono>
#include <iostream>

#include "geometry/plane.hpp"
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
            Vec3( 0.0, 0.0, 0.0),
            Orientation( 0.0, 0.0, 0.0),
            16 * 4, 9 * 4
        );

        auto plane = Plane(
            Vec3(10.0f, 0.0f,-2.0f),
            Vec3( 0.0f, 2.0f, 2.0f),
            Vec3( 0.0f,-2.0f, 2.0f)
        );

        for (unsigned int y = camera.getHeight(); y > 0; y--)
        {
            for (unsigned int x = 0; x < camera.getWidth(); x++)
            {
                float distance = plane.intersectRay(camera.getRayToPixel(x, y));
                if (distance <= 0.0f) std::cout << "  ";
                else std::cout << "@@";
            }
            std::cout << "|\n";
        }

        if (frameCount >= 1) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(frameCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e7 << " ms\n";
}
