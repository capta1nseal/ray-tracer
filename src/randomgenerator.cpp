#include "randomgenerator.hpp"


#include <random>

#include "raymath/constants.hpp"


RandomGenerator::RandomGenerator()
{
    std::random_device randomDevice;
    randomEngine.seed(randomDevice());

    unitDistribution = std::uniform_real_distribution<double>(0.0, 1.0);
    trigDistribution = std::uniform_real_distribution<double>(-1.0, 1.0);
    angleDistribution = std::uniform_real_distribution<double>(-pi, pi);
}
RandomGenerator::~RandomGenerator()
{
}

double RandomGenerator::randomLinearUnit()
{
    return unitDistribution(randomEngine);
}
double RandomGenerator::randomLinearTrig()
{
    return trigDistribution(randomEngine);
}
double RandomGenerator::randomLinearAngle()
{
    return angleDistribution(randomEngine);
}
