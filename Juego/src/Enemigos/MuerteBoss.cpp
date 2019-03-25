#include "MuerteBoss.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

MuerteBoss::MuerteBoss(float nX, float nY, float nZ, int maxVida)
: Enemigo(nX,nY,nZ,maxVida)
{
    Constantes constantes;
    funciona = true;
    atacado = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS; 
    rotation = constantes.CERO;

    _modelo = "assets/models/Muerte/Muerte.obj";
}

MuerteBoss::~MuerteBoss()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de MuerteBoss comportamiento en Enemigo
 * 
 * Entradas:
 * 
 * Salidas:
*/
void MuerteBoss::RunIA()
{
    Constantes constantes;
    if(this->getTimeMerodear() <= 0)
    {
        if(modo == constantes.UNO)
        {
            if(_ordenes[0] != EN_PERSIGUE && _ordenes[0] != EN_ATACAR)
            {
                this->ForzarCambioNodo(&constantes.CUATRO);
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

/***************** UpdateMuerteBoss *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del MuerteBoss
 * 
 * Entradas:
 *      i: (sennala al MuerteBoss del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/ 

void MuerteBoss::UpdateMuerteBoss(int* _jug)
{
    Jugador* _jugador = (Jugador*)_jug;
    Constantes constantes;
    funciona = true;
    if(modo == constantes.UNO && _ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_PERSIGUE: //La muerte se mueve
                funciona = this->perseguir(_jug);
                break;
        
            case EN_ATACAR: //La muerte ataca
                {
                    if(!atacado)
                    {
                        int danyo;
                        danyo = this->Atacar(-1);
                        
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
            case EN_VER: //La muerte ve al jugador
                {
                    if(this->ver(constantes.UNO, constantes.NUEVE * constantes.DIEZ))
                    {
                        funciona = true;
                    }
                    else 
                    {
                        funciona = false;
                    }
                }
                break;


            default:
                break;
        }
    }
}

void MuerteBoss::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}