#include "Interactuable.hpp"


Interactuable::Interactuable()
{

}
Interactuable::Interactuable(int codigo, int anc, int lar, int alt, const char *objeto, const char *textura, int posicion)
{
    std::string name_objeto(objeto);
    cadena_objeto = new char[sizeof(name_objeto)];
    strcpy(cadena_objeto, name_objeto.c_str());
     
    std::string name_textura(textura);
    cadena_textura = new char[sizeof(name_textura)];
    strcpy(cadena_textura, name_textura.c_str());

    codigoObjeto = codigo;
    ancho = anc;
    largo = lar;
    alto = alt;
    ruta_objeto = cadena_objeto; // deberia recoger *objeto pero se corrompe en la segunda iteracion del bucle
    ruta_textura = cadena_textura;
    posicionObjeto = posicion;
    accionado = false;
}

bool Interactuable::accionar()
{
    if(accionado)
    {
        accionado = false;
    }
    else accionado = true;
    return accionado;
}

/*************** moverseEntidad *****************
 * Funcion con la que el arma se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Interactuable::moverseEntidad(float updTime)
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
void Interactuable::RotarEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = rotateTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    rx = lastRx * (1 - pt) + newRx * pt;
    ry = lastRy * (1 - pt) + newRy * pt;
    rz = lastRz * (1 - pt) + newRz * pt;
}

void Interactuable::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

void Interactuable::UpdateTimeRotate(float updTime)
{
    rotateTime += updTime;
}
void Interactuable::setPosiciones(float nx,float ny,float nz)
{
    x = nx;
    y = ny;
    z = nz;
}

void Interactuable::setLastPosiciones(float nx,float ny,float nz)
{
    lastX = nx;
    lastY = ny;
    lastZ = nz;
}

void Interactuable::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(newX, newY, newZ);
    newX = nx;
    newY = ny;
    newZ = nz;
}

void Interactuable::setRotacion(float nrx, float nry, float nrz)
{
    rx = nrx;
    ry = nry;
    rz = nrz;
}

void Interactuable::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion(newRx, newRy, newRz);
    newRx = nrx;
    newRy = nry;
    newRz = nrz;
}

void Interactuable::setLastRotacion(float nrx, float nry, float nrz)
{
    lastRx = nrx;
    lastRy = nry;
    lastRz = nrz;
}

void Interactuable::initPosicionesFisicas(float nx,float ny,float nz)
{
    fisX = nx;
    fisY = ny;
    fisZ = nz;
}

void Interactuable::setPosicionesFisicas(float nx,float ny,float nz)
{
    fisX += nx;
    fisY += ny;
    fisZ += nz;
}

int Interactuable::getCodigo()
{
    return codigoObjeto;
}

const char* Interactuable::getObjeto()
{
    return ruta_objeto;
}

float Interactuable::getX()
{
    return x;
}

float Interactuable::getY()
{
    return y;
}

float Interactuable::getZ()
{
    return z;
}

float Interactuable::getNewX()
{
    return newX;
}

float Interactuable::getNewY()
{
    return newY;
}

float Interactuable::getNewZ()
{
    return newZ;
}

float Interactuable::getLastX()
{
    return lastX;
}

float Interactuable::getLastY()
{
    return lastY;
}

float Interactuable::getLastZ()
{
    return lastZ;
}

float Interactuable::getFisX()
{
    return fisX;
}

float Interactuable::getFisY()
{
    return fisY;
}

float Interactuable::getFisZ()
{
    return fisZ;
}

float Interactuable::getRX()
{
    return rx;
}

float Interactuable::getRY()
{
    return ry;
}

float Interactuable::getRZ()
{
    return rz;
}

void Interactuable::setID(int nid)
{
    id = nid;
}

int Interactuable::getID()
{
    return id;
}


const char* Interactuable::getTextura()
{
    return ruta_textura;
}
float Interactuable::getAncho()
{
    return ancho;
}
float Interactuable::getLargo()
{
    return largo;
}
float Interactuable::getAlto()
{
    return alto;
}

int Interactuable::GetPosicionObjetos()
{
    return posicionObjeto;
}
