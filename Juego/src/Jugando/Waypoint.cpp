#include <cstring>
#include "Waypoint.hpp"

Waypoint::Waypoint()
{
    posicion.x = 0.0f;
    posicion.y = 0.0f;
    posicion.z = 0.0f;
}

Waypoint::Waypoint(int ID_lectura, int x, int y, int z, int* arrayConexiones, int sizeConexiones)
{
    posicion.x = x;
    posicion.y = y;
    posicion.z = z;
    ID = ID_lectura;
    sizeIDConexiones = sizeConexiones;
    IDConexiones = arrayConexiones;
}

Waypoint::~Waypoint()
{
    posicion.x = 0;
    posicion.y = 0;
    posicion.z = 0;
    sizeIDConexiones = 0;
    ID = 0;
    delete IDConexiones;
    IDConexiones = nullptr;
}

void Waypoint::AnnadirConexionesWaypoints(Waypoint* waypointNivel)
{
    conexiones.push_back(waypointNivel);
}

short Waypoint::ContainsConection(short id)
{
     unsigned short i = 0;
    //Se comprueba el id pasado por parametro por los id del array
    while(i < sizeIDConexiones)
    {
        //Si se encuentra el array el id devuelve true ya que si lo contiene
        if(IDConexiones[i] == id)
        {
            return IDConexiones[i];
        }
        i++;
    }
    return -1;
}

short Waypoint::GetID()
{
    return ID;
}

int* Waypoint::GetIDConexiones()
{
    return IDConexiones;
}

vector <Waypoint*> Waypoint::GetConexiones()
{
    return conexiones;
}