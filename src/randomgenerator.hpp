#ifndef _RAYTRACERRANDOMGENERATOR_
#define _RAYTRACERRANDOMGENERATOR_


#include <random>


class RandomGenerator
{
public:
    RandomGenerator();
    ~RandomGenerator();

    double randomLinearUnit();
    double randomLinearTrig();
    double randomLinearAngle();

private:
    std::mt19937 randomEngine;
    std::uniform_real_distribution<double> unitDistribution;
    std::uniform_real_distribution<double> trigDistribution;
    std::uniform_real_distribution<double> angleDistribution;
};


#endif
