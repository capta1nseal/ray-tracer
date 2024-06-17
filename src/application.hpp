#ifndef _RAYTRACERAPPLICATION_
#define _RAYTRACERAPPLICATION_


#include "world.hpp"


/*
A wrapper class initializing and facilitating the execution of the program.
*/
class RayTracerApplication
{
public:
    RayTracerApplication();

    void run();

private:
    World world;
};


#endif
