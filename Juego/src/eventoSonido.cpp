#include "eventoSonido.hpp"

eventoSonido::eventoSonido(int inten,double durac,int nx,int ny,int nz,int prop,int tip)
{
    intensidad = inten;
    duracion = durac;
    x = nx;
    y = ny;
    z = nz;
    propietario = prop;
    tipo = tip;
}

eventoSonido::~eventoSonido()
{
    
}

int * eventoSonido::getPropiedades()
{
    int * datos = new int[7];
    datos[0] = intensidad ;
    datos[1] = duracion ;
    datos[2] = x ;
    datos[3] = y ;
    datos[4] = z ;
    datos[5] = propietario;
    datos[6] = tipo;
    return datos;
}

void eventoSonido::restarTiempo(double tiempo)
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

double eventoSonido::getDuracion()
{
    return duracion;
}