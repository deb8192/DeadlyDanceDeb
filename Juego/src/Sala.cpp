#include "Sala.hpp"

Sala::Sala(int anch,int larg, int alt, int nx, int ny, int nz, int type)
{
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

 Sala::~Sala(void)
 {
    if(entradas.size()>0)
    {
        for(std::size_t i=0;i<entradas.size();i++)
        {
            entradas[i]->~Sala();
        }
    }
    if(salidas.size()>0)
    {    
        for(std::size_t i=0;i<salidas.size();i++)
        {
            salidas[i]->~Sala();
        }
    }
 }

void Sala::agregarEntrada(Sala * plataforma)
{
    entradas.push_back(plataforma);
}

void Sala::agregarSalida(Sala * plataforma)
{
    salidas.push_back(plataforma);
}

int * Sala::getSizes()
{
    int * valores = new int[6];
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

void Sala::definirID(int id)
{
    posicion_en_grafica = id;
}
int Sala::getPosicionEnGrafica()
{
    return posicion_en_grafica;
}