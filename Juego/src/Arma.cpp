#include "Arma.hpp"

Arma::Arma()
{

}
Arma::Arma(int ataque)
{
    //motor = MotorGrafico::getInstance();
    //potenciaAtaque = ataque;
    //motor->CargarArmaEspecial(0,0,0,ruta,"");
}
void Arma::setPosiciones(int nx,int ny,int nz)
{
    x = nx;
    y = ny;
    z = nz;
}
void Arma::setID(int nid)
{
    id = nid;
}

int Arma::getID()
{
    return id;
}