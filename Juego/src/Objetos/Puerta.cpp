#include "Puerta.hpp"
#include "../Motores/MotorFisicas.hpp"

Puerta::Puerta(int id, int codigo,
    int anc, int lar, int alt,
    float x, float y, float z, unsigned short tipoObj,
    float despX, float despZ, int accion)
: Interactuable(id, codigo, anc, lar, alt,
    x, y, z, tipoObj, despX, despZ, accion)
{    
    _modelo = "assets/models/Puertas/Puerta.obj";
    _textura = "assets/texture/Puerta.png";

    if(accion == 10)
    {
        _modelo = "assets/models/Puertas/PuertaPiedra.obj";
        _textura = "assets/texture/rocasuelo.png";
    }
}

Puerta::~Puerta()
{
    _modelo = nullptr;
    _textura = nullptr;
}

void Puerta::GirarPuerta(float rotacion, bool desdePalanca)
{
    if (rotacion >= 0)
    {
        if (codigoObjeto == 0) // Puertas sin llave o palanca
        {
            //_motora->getEvent("AbrirPuerta")->setVolume(0.8f);
            _motora->getEvent("AbrirPuerta")->setPosition(posActual.x, posActual.y, posActual.z);
            _motora->getEvent("AbrirPuerta")->start();
        }
        else
        {
            if (desdePalanca) // Puertas con palancas
            {
                // TO DO: cambiar AbrirPuerta por sonido de engranaje
                _motora->getEvent("AbrirPuerta")->setPosition(posActual.x, posActual.y, posActual.z);
                _motora->getEvent("AbrirPuerta")->setVolume(0.5);
                _motora->getEvent("AbrirPuerta")->start();
            }
            else // Puertas con llave
            {
                _motora->getEvent("AbrirCerradura")->setPosition(posActual.x, posActual.y, posActual.z);
                _motora->getEvent("AbrirCerradura")->setVolume(0.5);
                _motora->getEvent("AbrirCerradura")->start();
            }
        }
    }
    else
    {
        _motora->getEvent("AbrirPuerta")->stop();
        _motora->getEvent("AbrirCerradura")->stop();

        // TO DO: anyadir sonido engranaje si se cierra con palanca
        /* if (desdePalanca) // Puertas con palancas
        {

        }
        else
        {

        }*/

        _motora->getEvent("CerrarPuerta")->setPosition(posActual.x, posActual.y, posActual.z);
        _motora->getEvent("CerrarPuerta")->start();
    }
    
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    setNewRotacion(rotActual.x, rotActual.y + rotacion, rotActual.z);
    _fisicas->updatePuerta(posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y + rotacion, rotActual.z,
        _desplazamientos[0], _desplazamientos[1], posObstaculos);
    _fisicas = nullptr;
}

void Puerta::Render(float updTime, float drawTime)
{
    RotarEntidad(1 / updTime);
    UpdateTimeRotate(drawTime);

    // TO DO: Para evitar esto, cambiar las puertas2 del XML con el ancho y alto de la puerta como si fuera vertical
    if (tipoObjeto == constantes.PUERTA2) // Para las puertas horizontales
        _motor->mostrarObjetos(
            posActual.x, posActual.y, posActual.z,
            rotActual.x, rotActual.y+90, rotActual.z,
            posicionArrayObjetos
        );
    else
    {
        _motor->mostrarObjetos(
            posActual.x, posActual.y, posActual.z,
            rotActual.x, rotActual.y, rotActual.z,
            posicionArrayObjetos
        );
    }
}