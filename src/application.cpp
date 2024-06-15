#include "application.hpp"


#include <chrono>
#include <iostream>

#include "geometry/plane.hpp"


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

        auto plane = Plane(
            Vec3( 0.0f,-1.0f,-1.0f),
            Vec3( 0.0f, 0.0f, 2.0f),
            Vec3( 0.0f, 2.0f, 0.0f)
        );

        auto ray = Ray(
            Vec3(-6.9f, 0.5f,-0.5f),
            Vec3( 6.9f,-0.1f, 0.1f).normalized()
        );

        std::cout << "Ray: " << ray << "\n";

        std::cout << "Intersection distance: " << plane.intersectRay(ray) << "\n";

        if (frameCount >= 100) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(frameCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e7 << " ms\n";
}
