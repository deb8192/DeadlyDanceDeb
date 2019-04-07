#include <cstring>
#include "Waypoint.hpp"
#include "../Motores/MotorFisicas.hpp"

Waypoint::Waypoint()
{
    Constantes constantes;
    posicionWaypoint.x = 0.0f;
    posicionWaypoint.y = 0.0f;
    posicionWaypoint.z = 0.0f;
    ID = -1;
    tipo = constantes.WAYP_A;
    sizeIDConexiones = 0;
    IDConexiones = nullptr;
    esCompartido = false;
    posicionFisicasWaypoint = 0;
}

Waypoint::Waypoint(int ID_lectura, int x, int y, int z, int compartido, int* arrayConexiones, const char& tipoWaypoint, int sizeConexiones, int ancho)
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _motor = MotorGrafico::GetInstance();
    posicionWaypoint.x = x;
    posicionWaypoint.y = y;
    posicionWaypoint.z = z;
    ID = ID_lectura;
    tipo = tipoWaypoint;
    sizeIDConexiones = sizeConexiones;
    IDConexiones = arrayConexiones;
    if(compartido == 1)
    {
        esCompartido = true;
    }
    else esCompartido = false;
    posicionFisicasWaypoint = _fisicas->CrearCuerpoWaypoint(x/2, y/2, z/2, ancho);
    _fisicas = nullptr;
}

Waypoint::~Waypoint()
{
    posicionWaypoint.x = 0;
    posicionWaypoint.y = 0;
    posicionWaypoint.z = 0;
    sizeIDConexiones = 0;
    ID = 0;
    tipo = 0;
    delete IDConexiones;
    IDConexiones = nullptr;
    esCompartido = false;
    posicionFisicasWaypoint = 0;
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

bool Waypoint::GetCompartido()
{
    return esCompartido;
}

char Waypoint::GetTipo()
{
    return tipo;
}

INdrawable::Posiciones Waypoint::GetPosicionWaypoint()
{
    return posicionWaypoint;
}

vector <Waypoint*> Waypoint::GetConexiones()
{
    return conexiones;
}

void Waypoint::Render()
{
    Constantes constantes;
    _motor->dibujarObjetoTemporal(posicionWaypoint.x, posicionWaypoint.y, posicionWaypoint.z,
    0.0f, 0.0f, 0.0f,
    constantes.UNO, constantes.UNO, constantes.UNO, constantes.UNO);
}