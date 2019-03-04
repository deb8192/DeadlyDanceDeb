#include <iostream>

#ifndef Waypoint_HPP
#define Waypoint_HPP

using namespace std;

class Waypoint
{
    public:
        Waypoint(int x, int y, int z);
        ~Waypoint();

    private:
        
        using PosicionesWaypoint = struct {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
        } posicion;
        vector <Waypoint*> conexiones;
        vector <Sala*> salasDondeEsta;

};
#endif