#include "Arma.hpp"
#include <math.h>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

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
void Arma::setPosicionesArmaEsp(float nx,float ny,float nz, float ry)
{
    float mx = nx + 6.5*(sin(DEGTORAD*ry));
    float my = ny;
    float mz = nz + 6.5*(cos(DEGTORAD*ry));

    this->setPosiciones((int)mx,(int)my,(int)mz);
}
int Arma::getAtaque()
{
    return potenciaAtaque;
}
float Arma::getX()
{
    return x;
}
float Arma::getY()
{
    return y;
}
float Arma::getZ()
{
    return x;
}
void Arma::setID(int nid)
{
    id = nid;
}

int Arma::getID()
{
    return id;
}