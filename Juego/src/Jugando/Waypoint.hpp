#include <iostream>
#include "../Motores/INdrawable.hpp"
#include "../Motores/MotorGrafico.hpp"
#include "../ConstantesComunes.hpp"
#include <vector>

#ifndef Waypoint_HPP
#define Waypoint_HPP

using namespace std;

class Waypoint
{
    public:
        Waypoint();
        Waypoint(int ID_lectura, int x, int y, int z, int compartido, int* arrayConexiones, const char& tipoWaypoint, int sizeConexiones, int alto);
        ~Waypoint();
        void AnnadirConexionesWaypoints(Waypoint* waypointNivel);
        short ContainsConection(short id);
        void Render();
        // Getters & Setters

        short GetID();
        int* GetIDConexiones();
        bool GetCompartido();
        char GetTipo();
        INdrawable::Posiciones GetPosicionWaypoint();
        vector <Waypoint*> GetConexiones();

        INdrawable::Posiciones posicionWaypoint;        //Coordenadas en el mapa del waypoint
        vector <Waypoint*> conexiones;      //Waypoints con los que se conecta
        short ID;                  //ID del waypoint 
        int* IDConexiones;       //array con los ID de las conexiones que ayuda a rellenar el vector de conexiones
        short sizeIDConexiones;     //Total de conexiones del waypoint
        char tipo;                   //tipo del waypoint: a->central, b->acceso horizontal, c->acceso vertical
        unsigned short posicionFisicasWaypoint;    //Posicion del waypoint en el array de waypoints de las fisicas
        bool esCompartido;
        MotorGrafico *_motor;
};
#endif