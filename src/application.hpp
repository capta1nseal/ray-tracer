#ifndef _RAYTRACERAPPLICATION_
#define _RAYTRACERAPPLICATION_


#include "camera.hpp"
#include "scene.hpp"
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
    Scene scene;
    Camera<double> camera;
    RayTracer rayTracer;

    void initializeScene();
    void initializeCamera();
    void initializeRayTracer();
};


#endif
