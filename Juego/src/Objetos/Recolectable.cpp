#include "Recolectable.hpp"


Recolectable::Recolectable()
{

}

Recolectable::Recolectable(int codigo, int ataque, const char* nombre,
    int anc, int lar, int alt, const char* objeto, const char* textura,
    float x, float y, float z)
{
    // INdrawable
    posIni.x = x;
    posIni.y = y;
    posIni.z = z;

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

Recolectable::~Recolectable()
{
    // Recolectable
    potenciaAtaque = 0;
    codigoObjeto = 0;
    posicionArrayObjetos = 0;
    cantidad = 0;

    // INobjetos
    nombreObjeto = nullptr;
    delete cadena_nombre;

    ruta_objeto = nullptr;
    delete cadena_objeto;

    ruta_textura = nullptr;
    delete cadena_textura;

    ancho = 0;
    largo = 0;
    alto  = 0;

    // INdrawable
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