#include "application.hpp"


#include <chrono>
#include <iostream>
#include <random>

#include "camera.hpp"
#include "scene.hpp"
#include "geometry/geometry.hpp"
#include "material.hpp"
#include "frame.hpp"
#include "raymath/usefulfunctions.hpp"


RayTracerApplication::RayTracerApplication()
    : rayTracer(scene, camera)
{
    initializeScene();
    initializeCamera();
    initializeRayTracer();
}

void RayTracerApplication::initializeScene()
{
    Material groundMaterial = {
        {0.3, 0.3, 0.3},
        {0.9, 0.9, 0.9},
        {1.0, 1.0, 1.0},
        0.15,
        0.5,
        0.0
    };

    Material frameMaterial = {
        {0.5, 0.6, 0.3},
        {0.85, 0.85, 0.85},
        {1.0, 1.0, 1.0},
        0.3,
        0.67,
        0.0
    };

    Material ballMaterial = {
        {0.6, 0.3, 0.7},
        {0.7, 0.4, 0.8},
        {1.0, 1.0, 1.0},
        0.95,
        0.9,
        0.0
    };

    scene.addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3(-100.0, 0.0, 0.0),
            Vec3(100.0,-100.0, 0.0),
            Vec3(100.0, 100.0, 0.0)
        ),
        groundMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3(-2.0, 0.0, 0.0),
            Vec3( 2.0, 0.0, 4.0),
            Vec3( 2.0, 0.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3( 2.0, 0.0, 0.0),
            Vec3(-2.0, 0.0, 4.0),
            Vec3(-2.0, 0.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3( 0.0,-2.0, 0.0),
            Vec3( 0.0, 2.0, 4.0),
            Vec3( 0.0, 2.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject<double>(
        Plane(
            Vec3( 0.0, 2.0, 0.0),
            Vec3( 0.0,-2.0, 4.0),
            Vec3( 0.0,-2.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject<double>(
        Sphere(
            Vec3(0.0, 0.0, 5.0),
            2.0
        ),
        ballMaterial
    ));
}

void RayTracerApplication::initializeCamera()
{
    // Define terminal aspect ratio, then scale taking character height into account.

    unsigned int terminalWidth = 16;
    unsigned int terminalHeight = 9;

    double terminalCharHeight = 1.8;

    double terminalScale = 6.9;

    terminalWidth *= terminalScale * terminalCharHeight;
    terminalHeight *= terminalScale;

    camera = Camera<double>(
        Vec3(-17.0, 7.0, 10.0),
        Orientation( M_PI * 0.0, M_PI * -0.11, M_PI * 0.125),
        terminalWidth, terminalHeight,
        45.0 * M_PI / 180.0, terminalCharHeight
    );
}

void RayTracerApplication::initializeRayTracer()
{
    rayTracer.setCamera(camera);
    rayTracer.setMaxSamples(4096);
}

void RayTracerApplication::run()
{
    auto clock = std::chrono::steady_clock();
    auto start = clock.now();

    unsigned int frameFrequency = 128;

    const unsigned int& sampleCount = rayTracer.getSampleCount();
    const unsigned int& maxSamples = rayTracer.getMaxSamples();

    start = clock.now();

    bool running = true;
    while (running)
    {
        rayTracer.sampleFrame();

        // Draw frame at power of two sample counts for rapid initial noise reduction,
        // then at frameFrequency interval once it is reached.
        if (
            (sampleCount < frameFrequency and isZeroOrPowerOfTwo(sampleCount)) or
            (sampleCount) % frameFrequency == 0
        )
            std::cout << rayTracer.getFrame();
        
        if (sampleCount >= maxSamples) running = false;
    }

    // Ensure that the final image gets displayed,
    // mostly for cases where maxSamples % frameFrequency != 0.
    std::cout << rayTracer.getFrame();

    auto meanSampleDuration = (clock.now() - start).count() / static_cast<double>(rayTracer.getSampleCount());

    std::cout << "Average sample duration was: " << meanSampleDuration / 1e6 << " ms\n";
}
