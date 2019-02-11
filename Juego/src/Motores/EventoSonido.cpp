#include "EventoSonido.hpp"

EventoSonido::EventoSonido(int inten,double durac,int nx,int ny,int nz,int prop,int tip)
{
    intensidad = inten;
    duracion = durac;
    duracionOriginal = durac;
    x = nx;
    y = ny;
    z = nz;
    propietario = prop; //2 enemigo, 1 jugador (quien crea el sonido)
    tipo = tip; //1 jugador, 2 pedir ayuda
    multiplicador = ((float)intensidad)/((float)duracion);
}

EventoSonido::~EventoSonido()
{
    
}

int*  EventoSonido::getPropiedades()
{
    int*  datos = new int[7];
    datos[0] = intensidad;
    datos[1] = duracion ;
    datos[2] = x ;
    datos[3] = y ;
    datos[4] = z ;
    datos[5] = propietario;
    datos[6] = tipo;
    return datos;
}

void EventoSonido::restarTiempo(double tiempo)
{
    if(duracion-tiempo < 0)
    {
        duracion = 0;
    }
    else
    {
        duracion = duracion - tiempo;
    }
}

double EventoSonido::getDuracion()
{
    return duracion;
}

float EventoSonido::getIntensidad()
{
    float result = ((float)duracionOriginal)-((float)duracion);
    return (multiplicador*result);
}

int EventoSonido::getTipo()
{
    return tipo;
}