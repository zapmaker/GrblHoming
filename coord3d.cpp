#include "coord3d.h"

Coord3D::Coord3D()
    : x(0.0), y(0.0), z(0.0), c(0.0), stoppedZ(true), sliderZIndex(0)
{
}

bool Coord3D::operator==(const Coord3D& rhs)
{
    return (x == rhs.x && y == rhs.y && z == rhs.z && c == rhs.c) ;
}
