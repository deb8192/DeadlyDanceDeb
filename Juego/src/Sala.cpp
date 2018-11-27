#include "Sala.hpp"

Sala::Sala(int anch,int larg, int nx, int ny, int type)
{
    ancho = anch;
    largo = larg;
    x = nx;
    y = ny;
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
    int * valores = new int[4];
    valores[0] = ancho;
    valores[1] = largo;
    valores[2] = x; 
    valores[3] = y;
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