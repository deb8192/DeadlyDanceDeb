#include "Recolectable.hpp"
#include "../Motores/MotorFisicas.hpp"

Recolectable::Recolectable()
{

}

Recolectable::Recolectable(int id, int anc, int lar, int alt,
    float x, float y, float z, unsigned short tipoObj,
    int despX, int despZ)
{
    // TO DO: revisar, solo tienen id los objetos cargados del XML
    // el resto que se crea luego valen -1
    this->id = id;

    // INdrawable
    posIni.x = x;
    posIni.y = y;
    posIni.z = z;

    posActual.x = x;
    posActual.y = y;
    posActual.z = z;

    posFutura.x = x;
    posFutura.y = y;
    posFutura.z = z;

    posPasada.x = x;
    posPasada.y = y;
    posPasada.z = z;

    ancho = anc;
    largo = lar;
    alto = alt;

    //INobjetos
    tipoObjeto = tipoObj;
    unsigned short accion = 0;

    if (tipoObj == constantes.ORO)
    {
        _modelo = "assets/models/gold.obj";
        _textura = "assets/texture/gold.png";
        accion = 4;
    }
    else if (tipoObj == constantes.VIDA)
    {
        _modelo = "assets/models/powerup0.obj";
        _textura = "assets/texture/powerup0.png";
        accion = 4;
    }
    else if (tipoObj == constantes.ENERGIA)
    {
        _modelo = "assets/models/powerup1.obj";
        _textura = "assets/texture/powerup1.png";
        accion = 4;
    }
    else if (tipoObj == constantes.GUITARRA1) // GUITARRA
    {
        _modelo = "assets/models/Armas/Guitarras/guitarra-1.obj";
        _textura = "assets/texture/guitarra-1.png";
        accion = 2;
    }
    else if (tipoObj == constantes.GUITARRA2)
    {
        _modelo = "assets/models/Armas/Guitarras/guitarra-2.obj";
        _textura = "assets/texture/guitarra-2.png";
        accion = 2;
    }
    else if (tipoObj == constantes.GUITARRA3)
    {
        _modelo = "assets/models/Armas/Guitarras/guitarra-3.obj";
        _textura = "assets/texture/guitarra-3.png";
        accion = 2;
    }
    else if (tipoObj == constantes.ARPA1) // ARPA
    {
        _modelo = "assets/models/Armas/Arpas/arpa-1.obj";
        _textura = "assets/texture/arpa-1.png";
        accion = 2;
    }
    else if (tipoObj == constantes.ARPA2)
    {
        _modelo = "assets/models/Armas/Arpas/arpa-2.obj";
        _textura = "assets/texture/arpa-2.png";
        accion = 2;
    }
    else if (tipoObj == constantes.ARPA3)
    {
        _modelo = "assets/models/Armas/Arpas/arpa-3.obj";
        _textura = "assets/texture/arpa-3.png";
        accion = 2;
    }
    else if (tipoObj == constantes.FLAUTA1) // FLAUTA
    {
        _modelo = "assets/models/Armas/Flautas/flauta-1.obj";
        _textura = "assets/texture/flauta-1.png";
        accion = 2;
    }
    else if (tipoObj == constantes.FLAUTA2) // FLAUTA
    {
        _modelo = "assets/models/Armas/Flautas/flauta-2.obj";
        _textura = "assets/texture/flauta-2.png";
        accion = 2;
    }
    else if (tipoObj == constantes.FLAUTA3) // FLAUTA
    {
        _modelo = "assets/models/Armas/Flautas/flauta-3.obj";
        _textura = "assets/texture/flauta-3.png";
        accion = 2;
    }
    else if (tipoObj == constantes.LLAVE)
    {
        _modelo = "assets/models/llave.obj";
        _textura = nullptr;
        accion = 8;
    }
    else if (tipoObj == constantes.LLAVE_BOSS)
    {
        _modelo = "assets/models/llaveboss.obj";
        _textura = "assets/texture/llaveboss.png";
        accion = 8;
        tipoObjeto = constantes.LLAVE;
    }

    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    posArrayFisicas = _fisicas->CrearCuerpoRec(accion,x/2,y/2,z/2,ancho,alto,largo,despX,despZ);
    _fisicas = nullptr;
}

Recolectable::~Recolectable()
{
    // Recolectable
    potenciaAtaque = 0;
    codigoObjeto = 0;
    posicionArrayObjetos = 0;
    posArrayFisicas = 0;
    cantidad = 0;
    tipoObjeto = 0;

    // INobjetos
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
    else if(pt < 0.0f)
    {
        pt = 0.0f;
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

int Recolectable::getCodigo()
{
    return codigoObjeto;
}

void Recolectable::setCodigo(int codigo)
{
    codigoObjeto = codigo;
}

void Recolectable::setAtaque(int potAtq)
{
    potenciaAtaque = potAtq;
}

int Recolectable::getAtaque()
{
    return potenciaAtaque;
}

int Recolectable::GetPosicionArrayObjetos()
{
    return posicionArrayObjetos;
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

unsigned short Recolectable::GetPosArrayFis()
{
    return posArrayFisicas;
}
