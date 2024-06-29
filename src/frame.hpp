#ifndef _RAYTRACERFRAME_
#define _RAYTRACERFRAME_


#include <vector>
#include <ostream>

#include "raymath/raymath.hpp"


/*
Basic colour storage class.
Stores one std::vector<Vec3<double>> that is a sum of all colours added per pixel,
    and a partner std::vector<unsigned int> of addition counts.
Using at(x,y) divides that value by a count of additions, so the storage appears to be averaged.
This implementation info could be useful info if you run into unexpected behaviour.
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

    std::vector<unsigned int> additionCountBuffer;
    std::vector<Vec3<double>> frame;
};

std::ostream& operator<<(std::ostream& os, const Frame& frame);


#endif
