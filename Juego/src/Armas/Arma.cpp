#include "Arma.hpp"
#include "../ConstantesComunes.hpp"
#include <math.h>

Arma::Arma()
{

}

Arma::Arma(int ataque, int anc, int lar, int alt,
    unsigned short tipoObj)
{
    potenciaAtaque = ataque;
    ancho = anc;
    largo = lar;
    alto = alt;
    //motor->CargarArmaEspecial(0,0,0,ruta,"");

    // INobjetos
    tipoObjeto = tipoObj;

    Constantes constantes;
    if (tipoObj == constantes.GUITARRA) // GUITARRA
    {
        _modelo = "assets/models/Arma.obj";
        _textura = "assets/texture/Arma.png";
    }
    else if (tipoObj == constantes.ARPA)
    {
        _modelo = "assets/models/Arpa.obj";
        _textura = "assets/texture/Arpa.png";
    }
}

Arma::~Arma()
{
    // Arma
    potenciaAtaque = 0;

    // INobjetos
    ancho = 0;
    largo = 0;
    alto = 0;

    // INdrawable
    _modelo = nullptr;
    _textura = nullptr;

    posIni.x = 0;
    posIni.y = 0;
    posIni.z = 0;

    posActual.x = 0;
    posActual.y = 0;
    posActual.z = 0;

    posPasada.x = 0;
    posPasada.y = 0;
    posPasada.z = 0;

    posFutura.x = 0;
    posFutura.y = 0;
    posFutura.z = 0;

    posFisicas.x = 0;
    posFisicas.y = 0;
    posFisicas.z = 0;

    rotActual.x = 0;
    rotActual.y = 0;
    rotActual.z = 0;

    rotPasada.x = 0;
    rotPasada.y = 0;
    rotPasada.z = 0;

    rotFutura.x = 0;
    rotFutura.y = 0;
    rotFutura.z = 0;

    moveTime = 0;
    rotateTime = 0;
    rotation = 0;
    id = 0;
    animacion = 0;
    animacionAnterior = 0;
}

/*************** moverseEntidad *****************
 * Funcion con la que el arma se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Arma::moverseEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    posActual.x = posPasada.x * (1 - pt) + posFutura.x * pt;
    posActual.z = posPasada.z * (1 - pt) + posFutura.z * pt;
}

/*************** rotarEntidad *****************
 * Funcion con la que el arma rotara
 * sobre si mismo mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Arma::RotarEntidad(float updTime)
{
    Constantes constantes;
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    if(rotFutura.y == 0.0 && rotFutura.y < rotPasada.y)
    {
        rotPasada.y = 2 * constantes.PI_RADIAN - rotPasada.y;
    }

    else if(rotFutura.y == 0.0 && rotPasada.y < 0.0)
    {
        rotPasada.y = rotPasada.y + 2 * constantes.PI_RADIAN;
    }

    rotActual.x = rotPasada.x * (1 - pt) + rotFutura.x * pt;
    rotActual.y = rotPasada.y * (1 - pt) + rotFutura.y * pt;
    rotActual.z = rotPasada.z * (1 - pt) + rotFutura.z * pt;
}

void Arma::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

void Arma::setPosiciones(float nx,float ny,float nz)
{
    posActual.x = nx;
    posActual.y = ny;
    posActual.z = nz;
}

void Arma::setLastPosiciones(float nx,float ny,float nz)
{
    posPasada.x = nx;
    posPasada.y = ny;
    posPasada.z = nz;
}

void Arma::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(posFutura.x, posFutura.y, posFutura.z);
    posFutura.x = nx;
    posFutura.y = ny;
    posFutura.z = nz;
}

void Arma::setRotacion(float nrx, float nry, float nrz)
{
    rotActual.x = nrx;
    rotActual.y = nry;
    rotActual.z = nrz;
}

void Arma::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion(rotFutura.x, rotFutura.y, rotFutura.z);
    rotFutura.x = nrx;
    rotFutura.y = nry;
    rotFutura.z = nrz;
}

void Arma::setLastRotacion(float nrx, float nry, float nrz)
{
    rotPasada.x = nrx;
    rotPasada.y = nry;
    rotPasada.z = nrz;
}

void Arma::initPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x = nx;
    posFisicas.y = ny;
    posFisicas.z = nz;
}

void Arma::setPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x += nx;
    posFisicas.y += ny;
    posFisicas.z += nz;
}

void Arma::setPosicionesArmaEsp(float nx,float ny,float nz, float nry)
{
    Constantes constantes;
    float mx = nx + 6.5*(sin(constantes.DEG_TO_RAD*nry));
    float my = ny;
    float mz = nz + 6.5*(cos(constantes.DEG_TO_RAD*nry));

    this->setPosiciones((int)mx,(int)my,(int)mz);
}

void Arma::setAtaque(int danyo)
{
    potenciaAtaque = danyo;
}

int Arma::getAtaque()
{
    return potenciaAtaque;
}

float Arma::getX()
{
    return posActual.x;
}

float Arma::getY()
{
    return posActual.y;
}

float Arma::getZ()
{
    return posActual.z;
}

float Arma::getNewX()
{
    return posFutura.x;
}

float Arma::getNewY()
{
    return posFutura.y;
}

float Arma::getNewZ()
{
    return posFutura.z;
}

float Arma::getLastX()
{
    return posPasada.x;
}

float Arma::getLastY()
{
    return posPasada.y;
}

float Arma::getLastZ()
{
    return posPasada.z;
}

float Arma::getIniX()
{
    return posIni.x;
}

float Arma::getIniY()
{
    return posIni.y;
}

float Arma::getIniZ()
{
    return posIni.z;
}

float Arma::getFisX()
{
    return posFisicas.x;
}

float Arma::getFisY()
{
    return posFisicas.y;
}

float Arma::getFisZ()
{
    return posFisicas.z;
}

float Arma::getRX()
{
    return rotActual.x;
}

float Arma::getRY()
{
    return rotActual.y;
}

float Arma::getRZ()
{
    return rotActual.z;
}

void Arma::setID(int nid)
{
    id = nid;
}

int Arma::getID()
{
    return id;
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

unsigned short Arma::GetTipoObjeto()
{
    return tipoObjeto;
}

const char* Arma::GetModelo()
{
    return _modelo;
}

const char* Arma::GetTextura()
{
    return _textura;
}
