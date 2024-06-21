#ifndef _RAYTRACERFRAME_
#define _RAYTRACERFRAME_


#include <vector>
#include <ostream>

#include "raymath/vec3.hpp"


/*
Basic colour storage class.
Stores one std::vector<Vec3<double>> that accumulates all colours added per pixel.
They are averaged using a buffer of n. accesses / pixel only upon returning.
*/
class Frame
{
public:
    Frame(unsigned int initWidth, unsigned int initHeight);

    void addSample(unsigned int x, unsigned int y, const Vec3<double>& newValue);
    
    Vec3<double> at(unsigned int x, unsigned int y) const;

    unsigned int getWidth() const { return width; }
    unsigned int getHeight() const { return height; }

private:
    unsigned int width, height;

    std::vector<unsigned int> accessCountBuffer;
    std::vector<Vec3<double>> frame;
};

std::ostream& operator<<(std::ostream& os, const Frame& frame);


#endif
