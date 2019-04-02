#include "Recolectable.hpp"
#include "../ConstantesComunes.hpp"

Recolectable::Recolectable()
{

}

Recolectable::Recolectable(int codigo, int ataque, 
    int anc, int lar, int alt, float x, float y, float z, unsigned short tipoObj)
{
    Constantes constantes;

    // INdrawable
    posIni.x = x;
    posIni.y = y;
    posIni.z = z;

    ancho = anc;
    largo = lar;
    alto = alt;

    if ((tipoObj >= constantes.ARMA_INI) && 
        (tipoObj <= constantes.ARMA_FIN))
    {
        potenciaAtaque = ataque;
        codigoObjeto = constantes.ARMA;
    }
    else // Los powerups y la llave no tienen ataque
    {
        potenciaAtaque = 0;
        codigoObjeto = constantes.POWERUP;
        // Si es una llave, se reasigna en el switch
    }

    //INobjetos
    tipoObjeto = tipoObj;

    // TO DO: no me dejaba usar constantes
    switch (tipoObj)
    {
        case 7: // ARPA
        {
            _modelo = "assets/models/Arpa.obj";
            _textura = "assets/texture/Arpa.png";
        }
        break;

        case 8: // GUITARRA
        {
            _modelo = "assets/models/Arma.obj";
            _textura = "assets/texture/Arma.png";
        }
        break;

        case 9: // ORO
        {
            _modelo = "assets/models/gold.obj";
            _textura = "assets/texture/gold.png";
        }
        break;

        case 10: // VIDA
        {
            _modelo = "assets/models/powerup0.obj";
            _textura = "assets/texture/powerup0.png";
        }
        break;

        case 11: // ENERGIA
        {
            _modelo = "assets/models/powerup1.obj";
            _textura = "assets/texture/powerup1.png";
        }
        break;

        case 1: // Llave
        {
            _modelo = "assets/models/llave.obj";
            _textura = nullptr;
            codigoObjeto = codigo;
        }
        break;
    }
}

Recolectable::~Recolectable()
{
    // Recolectable
    potenciaAtaque = 0;
    codigoObjeto = 0;
    posicionArrayObjetos = 0;
    cantidad = 0;

    // INobjetos
    delete cadena_nombre;

    ancho = 0;
    largo = 0;
    alto  = 0;

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
void Recolectable::moverseEntidad(float updTime)
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
void Recolectable::RotarEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    rotActual.x = rotPasada.x * (1 - pt) + rotFutura.x * pt;
    rotActual.y = rotPasada.y * (1 - pt) + rotFutura.y * pt;
    rotActual.z = rotPasada.z * (1 - pt) + rotFutura.z * pt;
}

void Recolectable::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

void Recolectable::setPosiciones(float nx,float ny,float nz)
{
    posActual.x = nx;
    posActual.y = ny;
    posActual.z = nz;
}

void Recolectable::setLastPosiciones(float nx,float ny,float nz)
{
    posPasada.x = nx;
    posPasada.y = ny;
    posPasada.z = nz;
}

void Recolectable::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(posFutura.x, posFutura.y, posFutura.z);
    posFutura.x = nx;
    posFutura.y = ny;
    posFutura.z = nz;
}

void Recolectable::setRotacion(float nrx, float nry, float nrz)
{
    rotActual.x = nrx;
    rotActual.y = nry;
    rotActual.z = nrz;
}

void Recolectable::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion(rotFutura.x, rotFutura.y, rotFutura.z);
    rotFutura.x = nrx;
    rotFutura.y = nry;
    rotFutura.z = nrz;
}

void Recolectable::setLastRotacion(float nrx, float nry, float nrz)
{
    rotPasada.x = nrx;
    rotPasada.y = nry;
    rotPasada.z = nrz;
}

void Recolectable::initPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x = nx;
    posFisicas.y = ny;
    posFisicas.z = nz;
}

void Recolectable::setPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x += nx;
    posFisicas.y += ny;
    posFisicas.z += nz;
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

float Recolectable::getX()
{
    return posActual.x;
}

float Recolectable::getY()
{
    return posActual.y;
}

float Recolectable::getZ()
{
    return posActual.z;
}

float Recolectable::getNewX()
{
    return posFutura.x;
}

float Recolectable::getNewY()
{
    return posFutura.y;
}

float Recolectable::getNewZ()
{
    return posFutura.z;
}

float Recolectable::getLastX()
{
    return posPasada.x;
}

float Recolectable::getLastY()
{
    return posPasada.y;
}

float Recolectable::getLastZ()
{
    return posPasada.z;
}

float Recolectable::getIniX()
{
    return posIni.x;
}

float Recolectable::getIniY()
{
    return posIni.y;
}

float Recolectable::getIniZ()
{
    return posIni.z;
}

float Recolectable::getFisX()
{
    return posFisicas.x;
}

float Recolectable::getFisY()
{
    return posFisicas.y;
}

float Recolectable::getFisZ()
{
    return posFisicas.z;
}

float Recolectable::getRX()
{
    return rotActual.x;
}

float Recolectable::getRY()
{
    return rotActual.y;
}

float Recolectable::getRZ()
{
    return rotActual.z;
}

void Recolectable::setID(int nid)
{
    id = nid;
}

int Recolectable::getID()
{
    return id;
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

// Devuelve si es una llave u otra cosa
unsigned short Recolectable::GetTipoObjeto()
{
    return tipoObjeto;
}

const char* Recolectable::GetModelo()
{
    return _modelo;
}

const char* Recolectable::GetTextura()
{
    return _textura;
}
