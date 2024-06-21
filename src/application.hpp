#ifndef _RAYTRACERAPPLICATION_
#define _RAYTRACERAPPLICATION_


#include "scene.hpp"


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
};


#endif
