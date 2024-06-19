#include "frame.hpp"


#include <vector>

#include "raymath/vec3.hpp"


Frame::Frame(unsigned int initWidth, unsigned int initHeight)
    : width(initWidth), height(initHeight)
{
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    accessCountBuffer.resize(width * height, 0);
    frame.resize(width * height, Vec3<double>(0.0, 0.0, 0.0));
}

void Frame::add(unsigned int x, unsigned int y, const Vec3<double>& newValue)
{
    if (x > width - 1 or y > height - 1) return;

    accessCountBuffer[y * width + x]++;
    frame[y * width + x] += newValue;
}

Vec3<double> Frame::at(unsigned int x, unsigned int y) const
{
    if (x > width - 1 or y > height - 1) return {0.0, 0.0, 0.0};
    return frame[y * width + x] * 1.0 / static_cast<double>(accessCountBuffer[y * width + x]);
}
