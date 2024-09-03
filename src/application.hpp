#ifndef _RAYTRACERAPPLICATION_
#define _RAYTRACERAPPLICATION_


#include <memory>

#include "randomgenerator.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "raytracer.hpp"


/*
A wrapper class initializing and facilitating the execution of the program.
*/
class RayTracerApplication
{
public:
    RayTracerApplication();

    void run();

private:
    std::shared_ptr<RandomGenerator> randomGenerator;
    Scene scene;
    Camera camera;
    RayTracer rayTracer;

    void initializeScene();
    void initializeCamera();
    void initializeRayTracer();
};


#endif
