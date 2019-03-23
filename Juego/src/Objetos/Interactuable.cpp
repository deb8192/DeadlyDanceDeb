#include "Interactuable.hpp"

Interactuable::Interactuable(int codigo, const char* nombre,
    int anc, int lar, int alt, int posicion, float x, float y, float z,
    unsigned short tipoObj)
{
    _motor = MotorGrafico::GetInstance();
    
    // INdrawable
    posIni.x = x;
    posIni.y = y;
    posIni.z = z;
    
    std::string name_nombre(nombre);
    cadena_nombre = new char[sizeof(name_nombre)];
    strcpy(cadena_nombre, name_nombre.c_str());

    nombreObjeto = cadena_nombre;
    codigoObjeto = codigo;
    ancho = anc;
    largo = lar;
    alto = alt;
    //ruta_objeto = cadena_objeto; // deberia recoger *objeto pero se corrompe en la segunda iteracion del bucle
    //ruta_textura = cadena_textura;
    posicionArrayObjetos = posicion;
    accionado = false;

    //INobjetos
    tipoObjeto = tipoObj;
}

Interactuable::~Interactuable()
{
    // Interactuable
    _motor = nullptr;
    codigoObjeto=0;
    accionado=0;
    posicionArrayObjetos=0;

    // TO DO: revisar cuando se cambie
    for(unsigned short i=0; i<tam-1; ++i)
    {
        _desplazamientos[i]=0;
    }
    delete[] _desplazamientos;

    // INobjetos
    nombreObjeto = nullptr;
    delete cadena_nombre;

    /*ruta_objeto = nullptr;
    delete cadena_objeto;

    ruta_textura = nullptr;
    delete cadena_textura;*/
    
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

bool Interactuable::accionar()
{
    
    accionado = !accionado;
    
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

    posActual.x = posPasada.x * (1 - pt) + posFutura.x * pt;
    posActual.z = posPasada.z * (1 - pt) + posFutura.z * pt;
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

    rotActual.x = rotPasada.x * (1 - pt) + rotFutura.x * pt;
    rotActual.y = rotPasada.y * (1 - pt) + rotFutura.y * pt;
    rotActual.z = rotPasada.z * (1 - pt) + rotFutura.z * pt;
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
    posActual.x = nx;
    posActual.y = ny;
    posActual.z = nz;
}

void Interactuable::setLastPosiciones(float nx,float ny,float nz)
{
    posPasada.x = nx;
    posPasada.y = ny;
    posPasada.z = nz;
}

void Interactuable::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(posFutura.x, posFutura.y, posFutura.z);
    posFutura.x = nx;
    posFutura.y = ny;
    posFutura.z = nz;
}

void Interactuable::setDesplazamientos(float despX, float despZ)
{
    _desplazamientos[0] = despX;
    _desplazamientos[1] = despZ;
}

void Interactuable::setRotacion(float nrx, float nry, float nrz)
{
    rotActual.x = nrx;
    rotActual.y = nry;
    rotActual.z = nrz;
}

void Interactuable::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion(rotFutura.x, rotFutura.y, rotFutura.z);
    rotFutura.x = nrx;
    rotFutura.y = nry;
    rotFutura.z = nrz;
}

void Interactuable::setLastRotacion(float nrx, float nry, float nrz)
{
    rotPasada.x = nrx;
    rotPasada.y = nry;
    rotPasada.z = nrz;
}

void Interactuable::initPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x = nx;
    posFisicas.y = ny;
    posFisicas.z = nz;
}

void Interactuable::setPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x += nx;
    posFisicas.y += ny;
    posFisicas.z += nz;
}

void Interactuable::SetPosicionArrayObjetos(int posicionObjeto)
{
    posicionArrayObjetos = posicionObjeto;
}


int Interactuable::GetPosicionArrayObjetos()
{
    return posicionArrayObjetos;
}
int Interactuable::getCodigo()
{
    return codigoObjeto;
}

/*const char* Interactuable::getNombre()
{
    return nombreObjeto;
}*/

const char* Interactuable::getObjeto()
{
    return ruta_objeto;
}

float Interactuable::getX()
{
    return posActual.x;
}

float Interactuable::getY()
{
    return posActual.y;
}

float Interactuable::getZ()
{
    return posActual.z;
}

float Interactuable::getNewX()
{
    return posFutura.x;
}

float Interactuable::getNewY()
{
    return posFutura.y;
}

float Interactuable::getNewZ()
{
    return posFutura.z;
}

float Interactuable::getLastX()
{
    return posPasada.x;
}

float Interactuable::getLastY()
{
    return posPasada.y;
}

float Interactuable::getLastZ()
{
    return posPasada.z;
}

float Interactuable::getIniX()
{
    return posIni.x;
}

float Interactuable::getIniY()
{
    return posIni.y;
}

float Interactuable::getIniZ()
{
    return posIni.z;
}

float Interactuable::getFisX()
{
    return posFisicas.x;
}

float Interactuable::getFisY()
{
    return posFisicas.y;
}

float Interactuable::getFisZ()
{
    return posFisicas.z;
}

float Interactuable::getRX()
{
    return rotActual.x;
}

float Interactuable::getRY()
{
    return rotActual.y;
}

float Interactuable::getRZ()
{
    return rotActual.z;
}

float * Interactuable::GetDesplazamientos()
{
    return _desplazamientos;
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
    return posicionArrayObjetos;
}

bool Interactuable::getAccionado()
{
  return accionado;
}

void Interactuable::Render(float updTime, float drawTime)
{
    RotarEntidad(1 / updTime);
    UpdateTimeRotate(drawTime);
    _motor->mostrarObjetos(
        posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y, rotActual.z,
        posicionArrayObjetos
    );
}

const char* Interactuable::GetModelo()
{
    return _modelo;
}

// Devuelve si es una puerta, palanca, cofre, llave
unsigned short Interactuable::GetTipoObjeto()
{
    return tipoObjeto;
}