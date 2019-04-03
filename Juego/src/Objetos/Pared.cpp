#include "Pared.hpp"

Pared::Pared(const char* nombre,
    int anc, int lar, int alt, float x, float y, float z,
    unsigned short tipoObj)
{
    //_motor = MotorGrafico::GetInstance();
    
    // INdrawable
    posIni.x = x;
    posIni.y = y;
    posIni.z = z;

    posActual.x = 0.0f;
    posActual.y = 0.0f;
    posActual.z = 0.0f;

    posFutura.x = 0.0f;
    posFutura.y = 0.0f;
    posFutura.z = 0.0f;

    posPasada.x = 0.0f;
    posPasada.y = 0.0f;
    posPasada.z = 0.0f;

    rotActual.x = 0.0f;
    rotActual.y = 0.0f;
    rotActual.z = 0.0f;

    rotFutura.x = 0.0f;
    rotFutura.y = 0.0f;
    rotFutura.z = 0.0f;

    rotPasada.x = 0.0f;
    rotPasada.y = 0.0f;
    rotPasada.z = 0.0f;

    posFisicas.x = 0.0f;
    posFisicas.y = 0.0f;
    posFisicas.z = 0.0f;

    rotation = 0.0f;
    moveTime = 0.0f;
    rotateTime = 0.0f;

    animacion = 0;
    animacionAnterior = 0;
    
    posicionArrayObjetos = 0;

    //INobjetos
    std::string name_nombre(nombre);
    cadena_nombre = new char[sizeof(name_nombre)];
    strcpy(cadena_nombre, name_nombre.c_str());

    nombreObjeto = cadena_nombre;
    ancho = anc;
    largo = lar;
    alto = alt;
    tipoObjeto = tipoObj;

    //Pared
    tam = 2;
}

Pared::~Pared()
{
    // Pared
    //_motor = nullptr;

    // INobjetos
    nombreObjeto = nullptr;
    delete cadena_nombre;
    cadena_nombre = nullptr;
    
    ancho = 0;
    largo = 0;
    alto  = 0;
    tipoObjeto = 0;

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
    
    //Pared
    tam = 0;
    posicionArrayObjetos = 0;
}


/*************** moverseEntidad *****************
 * Funcion con la que el arma se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Pared::moverseEntidad(float updTime)
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
void Pared::RotarEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = rotateTime / updTime;

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

void Pared::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

void Pared::UpdateTimeRotate(float updTime)
{
    rotateTime += updTime;
}
void Pared::setPosiciones(float nx,float ny,float nz)
{
    posActual.x = nx;
    posActual.y = ny;
    posActual.z = nz;
}

void Pared::setLastPosiciones(float nx,float ny,float nz)
{
    posPasada.x = nx;
    posPasada.y = ny;
    posPasada.z = nz;
}

void Pared::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(posFutura.x, posFutura.y, posFutura.z);
    posFutura.x = nx;
    posFutura.y = ny;
    posFutura.z = nz;
}

void Pared::setRotacion(float nrx, float nry, float nrz)
{
    rotActual.x = nrx;
    rotActual.y = nry;
    rotActual.z = nrz;
}

void Pared::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion(rotFutura.x, rotFutura.y, rotFutura.z);
    rotFutura.x = nrx;
    rotFutura.y = nry;
    rotFutura.z = nrz;
}

void Pared::setLastRotacion(float nrx, float nry, float nrz)
{
    rotPasada.x = nrx;
    rotPasada.y = nry;
    rotPasada.z = nrz;
}

void Pared::initPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x = nx;
    posFisicas.y = ny;
    posFisicas.z = nz;
}

void Pared::setPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x += nx;
    posFisicas.y += ny;
    posFisicas.z += nz;
}

void Pared::SetPosicionArrayObjetos(int posicionObjeto)
{
    posicionArrayObjetos = posicionObjeto;
}


int Pared::GetPosicionArrayObjetos()
{
    return posicionArrayObjetos;
}

float Pared::getX()
{
    return posActual.x;
}

float Pared::getY()
{
    return posActual.y;
}

float Pared::getZ()
{
    return posActual.z;
}

float Pared::getNewX()
{
    return posFutura.x;
}

float Pared::getNewY()
{
    return posFutura.y;
}

float Pared::getNewZ()
{
    return posFutura.z;
}

float Pared::getLastX()
{
    return posPasada.x;
}

float Pared::getLastY()
{
    return posPasada.y;
}

float Pared::getLastZ()
{
    return posPasada.z;
}

float Pared::getIniX()
{
    return posIni.x;
}

float Pared::getIniY()
{
    return posIni.y;
}

float Pared::getIniZ()
{
    return posIni.z;
}

float Pared::getFisX()
{
    return posFisicas.x;
}

float Pared::getFisY()
{
    return posFisicas.y;
}

float Pared::getFisZ()
{
    return posFisicas.z;
}

float Pared::getRX()
{
    return rotActual.x;
}

float Pared::getRY()
{
    return rotActual.y;
}

float Pared::getRZ()
{
    return rotActual.z;
}

void Pared::setID(int nid)
{
    id = nid;
}

int Pared::getID()
{
    return id;
}

float Pared::getAncho()
{
    return ancho;
}
float Pared::getLargo()
{
    return largo;
}
float Pared::getAlto()
{
    return alto;
}

/*void Pared::Render(float updTime, float drawTime)
{
    RotarEntidad(1 / updTime);
    UpdateTimeRotate(drawTime);
    _motor->mostrarObjetos(
        posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y, rotActual.z,
        posicionArrayObjetos
    );
}*/

const char* Pared::GetModelo()
{
    return _modelo;
}

// Devuelve si es una puerta, palanca, cofre, llave
unsigned short Pared::GetTipoObjeto()
{
    return tipoObjeto;
}