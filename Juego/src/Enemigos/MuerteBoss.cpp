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

    //TO DO: cambiar por el suyo
    _modelo = "assets/models/guardian_m/GuardianMuerteConTextura.obj";
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
            case EN_VER: //La muerte ve al jugador
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
            
            case EN_MERODEA: //La muerte merodea
                {
                    if(!hecho)
                    {
                        //Merodea estableciendo un nuevo angulo de rotacion
                        this->setRotation(this->randomBinomial() * maxRotacion);
                        //this->Merodear();
                        this->setTimeMerodear(1.5f);
                        hecho = true;
                        
                    }
                    else 
                    {
                        //Merodea poniendo en positivo o negativo el angulo actual de rotacion
                        int rota = rand() % 3 - 1;
                        if (rota != 0)
                        {
                            rotation *= rota;
                        }
                        //this->Merodear();
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO))
                        { 
                            modo = MODO_ATAQUE;
                        }
                    }
                    funciona = true;
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