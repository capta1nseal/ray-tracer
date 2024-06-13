#ifndef _RAYTRACERDIRECTION_
#define _RAYTRACERDIRECTION_


#include <ostream>


/*
azimuth and altitude will be between -pi and pi.
Any value passed into the initializer will be converted correctly from rad to rad.
Do conversions between degrees and rad yourself.
*/
struct Direction
{
    float azimuth;
    float altitude;

    Direction();
    Direction(float initAzimuth, float initAltitude);

    // outputs formatted direction to out stream
    friend std::ostream& operator<<(std::ostream& os, const Direction& direction);
};


#endif
