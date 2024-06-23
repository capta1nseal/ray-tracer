#include "application.hpp"


#include <chrono>
#include <iostream>
#include <random>

#include "camera.hpp"
#include "scene.hpp"
#include "geometry/geometry.hpp"
#include "material.hpp"
#include "frame.hpp"


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
    double terminalFontAspectRatio = 1.8;

    unsigned int terminalWidth = (16 * 8) * terminalFontAspectRatio;
    unsigned int terminalHeight = 9 * 8;

    camera = Camera<double>(
        Vec3(-17.0, 7.0, 10.0),
        Orientation( M_PI * 0.0, M_PI * -0.11, M_PI * 0.125),
        terminalWidth, terminalHeight,
        45.0 * M_PI / 180.0, terminalFontAspectRatio
    );
}

void RayTracerApplication::initializeRayTracer()
{
    rayTracer.setCamera(camera);
}

void RayTracerApplication::run()
{
    auto clock = std::chrono::steady_clock();
    auto start = clock.now();

    unsigned int frameFrequency = 128;

    start = clock.now();

    const unsigned int& sampleCount = rayTracer.getSampleCount();
    const unsigned int& maxSamples = rayTracer.getMaxSamples();

    bool running = true;
    while (running)
    {
        rayTracer.sampleFrame();

        if ((sampleCount - 1) % frameFrequency == 0 or sampleCount == maxSamples) std::cout << rayTracer.getFrame();
        
        if (sampleCount >= maxSamples) running = false;
    }

    auto frameDuration = (clock.now() - start).count() / static_cast<double>(rayTracer.getSampleCount());

    std::cout << "Average frame duration was: " << frameDuration / 1e6 << " ms\n";
}
