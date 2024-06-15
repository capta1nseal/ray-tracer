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

        auto camera = Camera();

        auto plane = camera.getTargetPlane();

        auto ray = Ray(
            Vec3(-6.9f, 0.5f,-0.5f),
            Vec3( 6.9f,-0.1f, 0.1f)
        );

        std::cout << "Intersection distance: " << plane.intersectRay(ray) << "\n";

        if (frameCount >= 100) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(frameCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e7 << " ms\n";
}
