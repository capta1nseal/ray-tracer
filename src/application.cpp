#include "application.hpp"


#include <chrono>
#include <iostream>

#include "raymath/raymath.hpp"


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

        std::cout << Vec3(Orientation(3.141f / 4.0f, 3.141f / 4.0f, 3.141f / 4.0f)) << "\n";


        if (frameCount >= 100) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(frameCount);

    std::cout << "Average frame duration was: " << frameDuration / 1e7 << " ms\n";
}
