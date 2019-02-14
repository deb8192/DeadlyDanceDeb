#include "Arma.hpp"
#include <math.h>


#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PIRADIAN 180.0f

Arma::Arma()
{

}
Arma::Arma(int ataque, const char*  nombre, int anc, int lar, int alt, const char* objeto, const char* textura)
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
    _nombreArma = cadena_nombre;
    ancho = anc;
    largo = lar;
    alto = alt;
    ruta_objeto = cadena_objeto; 
    ruta_textura = cadena_textura;
    //motor->CargarArmaEspecial(0,0,0,ruta,"");
}

Arma::~Arma()
{
    potenciaAtaque = 0.0f;
    if(_nombreArma != nullptr)
    {
        delete _nombreArma;
        _nombreArma = nullptr;
    }
    if(ruta_objeto != nullptr)
    {
        delete ruta_objeto;
        ruta_objeto = nullptr;
    }
    if(ruta_textura != nullptr)
    {
        delete ruta_textura;
        ruta_textura = nullptr;
    }
    ancho = 0.0f;
    largo = 0.0f;
    alto = 0.0f;
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
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    if(rotFutura.y == 0.0 && rotFutura.y < rotPasada.y)
    {
        rotPasada.y = 2 * PIRADIAN - rotPasada.y;
    }

    else if(rotFutura.y == 0.0 && rotPasada.y < 0.0)
    {
        rotPasada.y = rotPasada.y + 2 * PIRADIAN;
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
    float mx = nx + 6.5*(sin(DEGTORAD*nry));
    float my = ny;
    float mz = nz + 6.5*(cos(DEGTORAD*nry));

    this->setPosiciones((int)mx,(int)my,(int)mz);
}

void Arma::setNombre(const char* weaponName)
{
    _nombreArma = weaponName;
}

void Arma::setAtaque(int danyo)
{
    potenciaAtaque = danyo;
}

const char* Arma::getNombre()
{
    return _nombreArma;
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