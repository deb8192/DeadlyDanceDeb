#include "Arma.hpp"

Arma::Arma()
{

}
Arma::Arma(int ataque, const char * nombre)
{
    //motor = MotorGrafico::getInstance();
    potenciaAtaque = ataque;
    nombreArma = nombre;
    //motor->CargarArmaEspecial(0,0,0,ruta,"");
}
void Arma::setPosiciones(int nx,int ny,int nz)
{
    x = nx;
    y = ny;
    z = nz;
}
int Arma::getAtaque()
{
    return potenciaAtaque;
}
void Arma::setID(int nid)
{
    id = nid;
}

int Arma::getID()
{
    return id;
}