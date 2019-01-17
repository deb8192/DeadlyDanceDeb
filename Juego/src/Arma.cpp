#include "Arma.hpp"
#include <math.h>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Arma::Arma()
{

}
Arma::Arma(int ataque, const char * nombre, int anc, int lar, int alt, const char *objeto, const char *textura)
{
    std::string name_objeto(objeto);
    cadena_objeto = new char[sizeof(name_objeto)];
    strcpy(cadena_objeto, name_objeto.c_str());
     
    std::string name_textura(textura);
    cadena_textura = new char[sizeof(name_textura)];
    strcpy(cadena_textura, name_textura.c_str());

    std::string name_nombre(nombre);
    cadena_nombre = new char[sizeof(name_nombre)];
    strcpy(cadena_nombre, name_nombre.c_str());
    
    potenciaAtaque = ataque;
    nombreArma = cadena_nombre;
    ancho = anc;
    largo = lar;
    alto = alt;
    ruta_objeto = cadena_objeto; 
    ruta_textura = cadena_textura;
    //motor->CargarArmaEspecial(0,0,0,ruta,"");
}
void Arma::setPosiciones(float nx,float ny,float nz)
{
    x = nx;
    y = ny;
    z = nz;
}

void Arma::setLastPosiciones(float nx,float ny,float nz)
{
    lastX = nx;
    lastY = ny;
    lastZ = nz;
}

void Arma::setNewPosiciones(float nx,float ny,float nz)
{
    newX = nx;
    newY = ny;
    newZ = nz;
}

void Arma::initPosicionesFisicas(float nx,float ny,float nz)
{
    fisX = nx;
    fisY = ny;
    fisZ = nz;
}

void Arma::setPosicionesFisicas(float nx,float ny,float nz)
{
    fisX += nx;
    fisY += ny;
    fisZ += nz;
}
void Arma::setPosicionesArmaEsp(float nx,float ny,float nz, float ry)
{
    float mx = nx + 6.5*(sin(DEGTORAD*ry));
    float my = ny;
    float mz = nz + 6.5*(cos(DEGTORAD*ry));

    this->setPosiciones((int)mx,(int)my,(int)mz);
}

void Arma::setNombre(const char* weaponName)
{
    nombreArma = weaponName;
}

void Arma::setAtaque(int danyo)
{
    potenciaAtaque = danyo;
}

const char* Arma::getNombre()
{
    return nombreArma;
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
    return z;
}

float Arma::getNewX()
{
    return newX;
}

float Arma::getNewY()
{
    return newY;
}

float Arma::getNewZ()
{
    return newZ;
}

float Arma::getLastX()
{
    return lastX;
}

float Arma::getLastY()
{
    return lastY;
}

float Arma::getLastZ()
{
    return lastZ;
}

float Arma::getFisX()
{
    return fisX;
}

float Arma::getFisY()
{
    return fisY;
}

float Arma::getFisZ()
{
    return fisZ;
}

float Arma::getRX()
{
    return rx;
}

float Arma::getRY()
{
    return ry;
}

float Arma::getRZ()
{
    return rz;
}

void Arma::setID(int nid)
{
    id = nid;
}

int Arma::getID()
{
    return id;
}

const char* Arma::getObjeto()
{
    return ruta_objeto;
}
 
const char* Arma::getTextura()
{
    return ruta_textura;
}
float Arma::getAncho()
{
    return ancho;
}
float Arma::getLargo()
{
    return largo;
}
float Arma::getAlto()
{
    return alto;
}