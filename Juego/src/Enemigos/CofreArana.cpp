#include "CofreArana.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

CofreArana::CofreArana(float nX, float nY, float nZ, int maxVida,
    float anchoN, float altoN, float largoN)
: Enemigo(nX,nY,nZ,maxVida)
{
    Constantes constantes;
    funciona = true;
    atacado = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS;
    rotation = constantes.CERO;

    _modelo = "assets/models/Cofre/cofreArana.obj";
    _textura = "assets/texture/cofreArana.png";

    ancho = anchoN;
    largo = largoN;
    alto = altoN;
}

CofreArana::~CofreArana()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
    _textura = nullptr;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del CofreArana comportamiento en Enemigo
 *
 * Entradas:
 *
 * Salidas:
*/
void CofreArana::RunIA()
{
    Constantes constantes;
    if(this->getTimeMerodear() <= 0)
    {
        if(modo == constantes.UNO)
        {
            if(_ordenes[0] != EN_PERSIGUE && _ordenes[0] != EN_ATACAR)
            {
                this->ForzarCambioNodo(&constantes.DIEZ);
            }
        }
        if(atacado)
        {
            atacado = false;
        }
        if(hecho)
        {
            hecho = false;
        }
        _ordenes = this->Enemigo::RunIA(funciona);
    }
}

/***************** UpdateCofreArana *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del CofreArana
 *
 * Entradas:
 *      i: (sennala al CofreArana del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/

void CofreArana::UpdateCofreArana(short *i, int* _jug)
{
    Jugador* _jugador = (Jugador*)_jug;
    Constantes constantes;
    funciona = true;
    if(modo == MODO_ATAQUE && _ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_PERSIGUE: //El CofreArana se mueve
                funciona = this->perseguir(_jug);
                break;

            case EN_ATACAR: //El CofreArana ataca
                {
                    if(!atacado)
                    {
                        int danyo;
                        danyo = this->Atacar(*i);

                        if(danyo > 0)
                        {
                            _jugador->ModificarVida(-danyo);
                            funciona = true;
                            atacado = true;
                        }
                        else
                        {
                            funciona = false;
                        }
                    }
                }
                break;
        }
    }
    else if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_VER: //El CofreArana ve al jugador
                {
                    if(this->ver(constantes.UNO, constantes.SEIS * constantes.CINCO))
                    {
                        funciona = true;
                    }
                    else
                    {
                        funciona = false;
                    }
                }
                break;
        }
    }
}

void CofreArana::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}

float CofreArana::GetAncho()
{
    return ancho;
}

float CofreArana::GetAlto()
{
    return alto;
}

float CofreArana::GetLargo()
{
    return largo;
}
