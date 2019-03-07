#include "Sala.hpp"

Sala::Sala(int anch,int larg, int alt, int nx, int ny, int nz, int type)
{
    Constantes constantes;
    _waypoints.reserve(constantes.CINCO);
    ancho = anch;
    largo = larg;
    alto = alt;
    x = nx;
    y = ny;
    z = nz;
    if(type >= 0 && type <= 4)
    {
        tipocentro=type;
    }
    else
    {
        tipocentro = 0;//por defecto se coge el tipo 0 que es que esta en el centro
    }
}

 Sala::~Sala()
 {
    // Liberar memoria
    short tam = _waypoints.size();
    for(short i=0; i < tam; i++)
    {
        delete _waypoints.at(i);
    }
    _waypoints.clear();

    if (entradas.size() > 0)
    {
        for (unsigned short i=0; i<entradas.size(); ++i)
        {
            delete entradas.at(i);
        }
        entradas.clear();
    }
    
    if (salidas.size() > 0)
    {
        for (unsigned short i=0; i<salidas.size(); ++i)
        {
            delete salidas.at(i);
        }
        salidas.clear();
    }

    ancho = 0;
    largo = 0;
    alto = 0;
    x = 0;
    y = 0;
    z = 0;
    tipocentro = 0;
    posicion_en_grafica = 0;
 }

void Sala::agregarEntrada(Sala* plataforma)
{
    entradas.push_back(plataforma);
}

void Sala::agregarSalida(Sala* plataforma)
{
    salidas.push_back(plataforma);
}
/*********** AgregarWaypoint ***********
 * Funcion que annade los waypoints que se pasan
 * por parametro al vector de waypoints de la sal
 * 
 *      Entradas:
 *                  Waypoint* waypoint: waypoint a annadir al vector
 *      Salida:
*/
void Sala::AgregarWaypoint(Waypoint* waypoint)
{
    _waypoints.push_back(waypoint);
}

int* Sala::getSizes()
{
    int* valores = new int[6];
    valores[0] = ancho;
    valores[1] = largo;
    valores[2] = x; 
    valores[3] = y;
    valores[4] = z;
    valores[5] = alto;
    return valores;
}

int Sala::getType()
{
    return tipocentro;
}

std::vector<Sala*> Sala::getEntradas()
{
    return entradas;
}

std::vector<Sala*> Sala::getSalidas()
{
    return salidas;
}

std::vector<Waypoint*> Sala::GetWaypoints()
{
    return _waypoints;
}

void Sala::definirID(int id)
{
    posicion_en_grafica = id;
}
int Sala::getPosicionEnGrafica()
{
    return posicion_en_grafica;
}
