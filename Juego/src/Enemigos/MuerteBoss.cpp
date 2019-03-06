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

    _modelo = "assets/models/rockero.b3d";
}

MuerteBoss::~MuerteBoss()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del MuerteBoss comportamiento en Enemigo
 * 
 * Entradas:
 * 
 * Salidas:
*/
void MuerteBoss::RunIA()
{
    
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
            case EN_PERSIGUE: //El Pollo se mueve
                funciona = this->perseguir(_jug);
                break;
        
            case EN_ATACAR: //El Pollo ataca
                {
                    if(!atacado)
                    {
                        cout<<"intenta atacar"<<endl;
                        int danyo;
                        danyo = this->Atacar(-1);
                        
                        if(danyo > 0)
                        {
                            _jugador->ModificarVida(-danyo);
                            cout<<"Ataca por la IA" <<endl;
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
            case EN_VER: //El Pollo ve al jugador
                {
                    if(this->ver(constantes.UNO))
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
                cout<<"No hace nada"<<endl;
                break;
        }
    }
}

void MuerteBoss::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}