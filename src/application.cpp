#include "application.hpp"

#include <chrono>
#include <iostream>

#include "camera.hpp"
#include "frame.hpp"
#include "material.hpp"
#include "raymath/usefulfunctions.hpp"
#include "scene.hpp"

RayTracerApplication::RayTracerApplication()
    : randomGenerator(std::make_shared<RandomGenerator>(RandomGenerator())),
      rayTracer(scene, camera, randomGenerator) {
    initializeScene();
    initializeCamera();
    initializeRayTracer();
}

void RayTracerApplication::initializeScene() {
    // TODO move all this code into a scene initializing component. May be a
    // good time to move defined 3D objects into file-based storage.

    auto groundMaterial = materialLibrary.addMaterial(Material{
        {0.3, 0.3, 0.3}, {0.9, 0.9, 0.9}, {1.0, 1.0, 1.0}, 0.15, 0.5, 0.0});

    auto frameMaterial = materialLibrary.addMaterial(Material{
        {0.5, 0.6, 0.3}, {0.85, 0.85, 0.85}, {1.0, 1.0, 1.0}, 0.3, 0.67, 0.0});

    auto ballMaterial = materialLibrary.addMaterial(Material{
        {0.6, 0.3, 0.7}, {0.7, 0.4, 0.8}, {1.0, 1.0, 1.0}, 1.0, 1.0, 0.0});

    scene.addPrimitiveObject(
        PrimitiveObject(Plane(Vec3(-100.0, 0.0, 0.0), Vec3(100.0, -100.0, 0.0),
                              Vec3(100.0, 100.0, 0.0)),
                        groundMaterial));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(Vec3(-2.0, 0.0, 0.0), Vec3(2.0, 0.0, 4.0), Vec3(2.0, 0.0, 1.0)),
        frameMaterial));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(Vec3(2.0, 0.0, 0.0), Vec3(-2.0, 0.0, 4.0), Vec3(-2.0, 0.0, 1.0)),
        frameMaterial));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(Vec3(0.0, -2.0, 0.0), Vec3(0.0, 2.0, 4.0), Vec3(0.0, 2.0, 1.0)),
        frameMaterial));
    scene.addPrimitiveObject(PrimitiveObject(
        Plane(Vec3(0.0, 2.0, 0.0), Vec3(0.0, -2.0, 4.0), Vec3(0.0, -2.0, 1.0)),
        frameMaterial));
    scene.addPrimitiveObject(
        PrimitiveObject(Sphere(Vec3(0.0, 0.0, 5.0), 2.0), ballMaterial));

    // Test for rotation around axis.

    Vec3<double> sphereCenter = {0.0, 0.0, 5.0};
    Vec3<double> firstBallDelta = {-5.0, 0.0, 0.0};
    Vec3<double> axis = Vec3(-0.1, 0.2, 1.0).normalized();
    firstBallDelta = axis % (firstBallDelta % axis);

    for (double angle = 0.0; angle < tau - 0.001; angle += tau * (1.0 / 15.0)) {
        scene.addPrimitiveObject(PrimitiveObject(
            Sphere(sphereCenter + rotateAroundUnit(firstBallDelta, axis, angle),
                   0.75),
            ballMaterial));
    }
}

void RayTracerApplication::initializeCamera() {
    // Define terminal aspect ratio, then scale to full resolution taking
    // character height into account.

    unsigned int imageWidth = 640;
    unsigned int imageHeight = 360;

    camera =
        Camera(Vec3(-17.0, 7.0, 10.0),
               Orientation(M_PI * 0.0, M_PI * -0.11, M_PI * 0.125), imageWidth,
               imageHeight, 45.0 * M_PI / 180.0, randomGenerator);
}

void RayTracerApplication::initializeRayTracer() {
    rayTracer.setCamera(camera);
    rayTracer.setMaxSamples(4096);
}

void RayTracerApplication::run() {
    auto clock = std::chrono::steady_clock();
    auto start = clock.now();

    const unsigned int &sampleCount = rayTracer.getSampleCount();
    const unsigned int &maxSamples = rayTracer.getMaxSamples();

    start = clock.now();

    bool running = true;
    while (running) {
        rayTracer.sampleFrame();

        if (sampleCount >= maxSamples)
            running = false;
    }

    // Write result to a file.
    rayTracer.getFrame().writeToFile("testoutfile.png");

    auto meanSampleDuration = (clock.now() - start).count() /
                              static_cast<double>(rayTracer.getSampleCount());

    std::cout << "Average sample duration was: " << meanSampleDuration / 1e6
              << " ms\n";
}
