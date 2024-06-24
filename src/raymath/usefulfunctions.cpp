#include "usefulfunctions.hpp"


bool isPowerOfTwo(unsigned int x)
{
    return x != 0 && !(x & (x - 1));
}

bool isZeroOrPowerOfTwo(unsigned int x)
{
    return !(x & (x - 1));
}
