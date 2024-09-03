#include "application.hpp"


#include <chrono>
#include <iostream>

#include "camera.hpp"
#include "scene.hpp"
#include "geometry/geometry.hpp"
#include "material.hpp"
#include "frame.hpp"
#include "raymath/usefulfunctions.hpp"


RayTracerApplication::RayTracerApplication()
    : randomGenerator(std::make_shared<RandomGenerator>(RandomGenerator())), rayTracer(scene, camera, randomGenerator)
{
    initializeScene();
    initializeCamera();
    initializeRayTracer();
}

void RayTracerApplication::initializeScene()
{
    // TODO move all this code into a scene initializing component. May be a good time to move defined 3D objects into file-based storage.
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

    scene.addPrimitiveObject(PrimitiveObject(
        Plane(
            Vec3(-100.0, 0.0, 0.0),
            Vec3(100.0,-100.0, 0.0),
            Vec3(100.0, 100.0, 0.0)
        ),
        groundMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(
            Vec3(-2.0, 0.0, 0.0),
            Vec3( 2.0, 0.0, 4.0),
            Vec3( 2.0, 0.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(
            Vec3( 2.0, 0.0, 0.0),
            Vec3(-2.0, 0.0, 4.0),
            Vec3(-2.0, 0.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(
            Vec3( 0.0,-2.0, 0.0),
            Vec3( 0.0, 2.0, 4.0),
            Vec3( 0.0, 2.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(
            Vec3( 0.0, 2.0, 0.0),
            Vec3( 0.0,-2.0, 4.0),
            Vec3( 0.0,-2.0, 1.0)
        ),
        frameMaterial
    ));
    scene.addPrimitiveObject(PrimitiveObject(
        Sphere(
            Vec3(0.0, 0.0, 5.0),
            2.0
        ),
        ballMaterial
    ));

    // Test for rotation around axis.

    Vec3<double> sphereCenter = {0.0, 0.0, 5.0};
    Vec3<double> firstBallDelta = {-5.0, 0.0, 0.0};
    Vec3<double> axis = Vec3(-0.1, 0.2, 1.0).normalized();
    firstBallDelta = axis % (firstBallDelta % axis);

    for (double angle = 0.0; angle < tau - 0.001; angle += tau * (1.0 / 15.0))
    {
        scene.addPrimitiveObject(PrimitiveObject(
            Sphere(
                sphereCenter + rotateAroundUnit(firstBallDelta, axis, angle),
                0.75
            ),
            ballMaterial
        ));
    }
}

void RayTracerApplication::initializeCamera()
{
    // Define terminal aspect ratio, then scale to full resolution taking character height into account.

    unsigned int terminalWidth = 16;
    unsigned int terminalHeight = 9;

    // Relative character height hard-coded. Please use a monospace font.
    double terminalCharHeight = 1.8;

    // Amount to scale up aspect ratio by for final scale (in units of horizontal character width).
    double terminalScale = 23.63;

    terminalWidth *= terminalScale;
    terminalHeight *= terminalScale / terminalCharHeight;

    camera = Camera(
        Vec3(-17.0, 7.0, 10.0),
        Orientation( M_PI * 0.0, M_PI * -0.11, M_PI * 0.125),
        terminalWidth, terminalHeight,
        45.0 * M_PI / 180.0, terminalCharHeight,
        randomGenerator
    );
}

void RayTracerApplication::initializeRayTracer()
{
    rayTracer.setCamera(camera);
    rayTracer.setMaxSamples(16384);
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
        // then at intervals of frameFrequency once it is first reached.
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
