#include <iostream>
#include <iostream>
#include <vector>

#ifndef Waypoint_HPP
#define Waypoint_HPP

using namespace std;

class Waypoint
{
    public:
        Waypoint();
        Waypoint(int ID_lectura, int x, int y, int z, int* arrayConexiones, int sizeConexiones);
        ~Waypoint();
        void AnnadirConexionesWaypoints(Waypoint* waypointNivel);
        short ContainsConection(short id);
        // Getters & Setters

        short GetID();
        int* GetIDConexiones();
        vector <Waypoint*> GetConexiones();

    private:
        
        using PosicionesWaypoint = struct {
            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;
        };

        PosicionesWaypoint posicion;        //Coordenadas en el mapa del waypoint
        vector <Waypoint*> conexiones;      //Waypoints con los que se conecta
        short ID;                  //ID del waypoint 
        int* IDConexiones;       //array con los ID de las conexiones que ayuda a rellenar el vector de conexiones
        short sizeIDConexiones;
};
#endif