#include "Recolectable.hpp"


Recolectable::Recolectable()
{

}

Recolectable::~Recolectable()
{

}

Recolectable::Recolectable(int codigo, int ataque, const char *nombre, int anc, int lar, int alt, const char *objeto, const char *textura)
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

    codigoObjeto = codigo;
    potenciaAtaque = ataque;
    nombreObjeto = cadena_nombre;
    ancho = anc;
    largo = lar;
    alto = alt;
    ruta_objeto = cadena_objeto; // deberia recoger *objeto pero se corrompe en la segunda iteracion del bucle
    ruta_textura = cadena_textura;
}

/*************** moverseEntidad *****************
 * Funcion con la que el arma se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Recolectable::moverseEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    x = lastX * (1 - pt) + newX * pt;
    z = lastZ * (1 - pt) + newZ * pt;
}

/*************** rotarEntidad *****************
 * Funcion con la que el arma rotara
 * sobre si mismo mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Recolectable::RotarEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    rx = lastRx * (1 - pt) + newRx * pt;
    ry = lastRy * (1 - pt) + newRy * pt;
    rz = lastRz * (1 - pt) + newRz * pt;
}

void Recolectable::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

void Recolectable::setPosiciones(float nx,float ny,float nz)
{
    x = nx;
    y = ny;
    z = nz;
}

void Recolectable::setLastPosiciones(float nx,float ny,float nz)
{
    lastX = nx;
    lastY = ny;
    lastZ = nz;
}

void Recolectable::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(newX, newY, newZ);
    newX = nx;
    newY = ny;
    newZ = nz;
}

void Recolectable::setRotacion(float nrx, float nry, float nrz)
{
    rx = nrx;
    ry = nry;
    rz = nrz;
}

void Recolectable::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion(newRx, newRy, newRz);
    newRx = nrx;
    newRy = nry;
    newRz = nrz;
}

void Recolectable::setLastRotacion(float nrx, float nry, float nrz)
{
    lastRx = nrx;
    lastRy = nry;
    lastRz = nrz;
}

void Recolectable::initPosicionesFisicas(float nx,float ny,float nz)
{
    fisX = nx;
    fisY = ny;
    fisZ = nz;
}

void Recolectable::setPosicionesFisicas(float nx,float ny,float nz)
{
    fisX += nx;
    fisY += ny;
    fisZ += nz;
}

void Recolectable::SetPosicionArrayObjetos(int posicionObjeto)
{
    posicionArrayObjetos = posicionObjeto;
}

void Recolectable::setCantidad(int can)
{
    cantidad = can;
}

int Recolectable::getAtaque()
{
    return potenciaAtaque;
}

int Recolectable::GetPosicionArrayObjetos()
{
    return posicionArrayObjetos;
}

int Recolectable::getCodigo()
{
    return codigoObjeto;
}

const char* Recolectable::getNombre()
{
    return nombreObjeto;
}

const char* Recolectable::getObjeto()
{
    return ruta_objeto;
}

float Recolectable::getX()
{
    return x;
}

float Recolectable::getY()
{
    return y;
}

float Recolectable::getZ()
{
    return z;
}

float Recolectable::getNewX()
{
    return newX;
}

float Recolectable::getNewY()
{
    return newY;
}

float Recolectable::getNewZ()
{
    return newZ;
}

float Recolectable::getLastX()
{
    return lastX;
}

float Recolectable::getLastY()
{
    return lastY;
}

float Recolectable::getLastZ()
{
    return lastZ;
}

float Recolectable::getFisX()
{
    return fisX;
}

float Recolectable::getFisY()
{
    return fisY;
}

float Recolectable::getFisZ()
{
    return fisZ;
}

float Recolectable::getRX()
{
    return rx;
}

float Recolectable::getRY()
{
    return ry;
}

float Recolectable::getRZ()
{
    return rz;
}

void Recolectable::setID(int nid)
{
    id = nid;
}

int Recolectable::getID()
{
    return id;
}


const char* Recolectable::getTextura()
{
    return ruta_textura;
}
float Recolectable::getAncho()
{
    return ancho;
}
float Recolectable::getLargo()
{
    return largo;
}
float Recolectable::getAlto()
{
    return alto;
}

int Recolectable::getCantidad()
{
    return cantidad;
}
