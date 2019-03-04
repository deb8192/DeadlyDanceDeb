#include "Waypoint.hpp"

Waypoint::Waypoint(int x, int y, int z)
{
    posicion.x = x;
    posicion.y = y;
    posicion.z = z;
}

Waypoint::~Waypoint(int x, int y, int z)
{
    posicion.x = 0;
    posicion.y = 0;
    posicion.z = 0;
}