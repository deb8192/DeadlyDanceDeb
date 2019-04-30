#include "MuerteBoss.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

MuerteBoss::MuerteBoss(float nX, float nY, float nZ, int maxVida)
: Enemigo(nX,nY,nZ,maxVida)
{
    funciona = true;
    atacado = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS;
    rotation = constantes.CERO;

    _modelo = "assets/models/Muerte/Muerte.obj";
    _textura = "assets/texture/Muerte.png";
}

MuerteBoss::~MuerteBoss()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
    _textura = nullptr;
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
    if(modo == constantes.UNO)
    {
        if(_ordenes[0] != EN_PERSIGUE && _ordenes[0] != EN_ATACAR)
        {
            this->ForzarCambioNodo(&constantes.CINCO);
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

/***************** UpdateMuerteBoss *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del MuerteBoss
 *
 * Entradas:
 *      i: (sennala al MuerteBoss del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/

void MuerteBoss::UpdateMuerteBoss(short *i, int* _jug, bool ayuda)
{
    Jugador* _jugador = (Jugador*)_jug;
    funciona = true;
    if(modo == MODO_PELIGRO && _ordenes != nullptr)
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


    else if(modo == MODO_AUXILIAR_ALIADO)
    {
        this->AuxiliarAliado();
    }

    else if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_COMPROBAR: //Comprueba distintas condiciones del enemigo como su vida
                {
                    switch (_ordenes[1])
                    {
                        case EN_MAX_VIDA_33:
                            {
                                int porcentaje_33 = this->getVidaIni() * constantes.CIEN / constantes.MAX_VIDA_BOSS_PELIGRO;
                                if(this->getVida() <= porcentaje_33)
                                {
                                    funciona = true;
                                }
                                else {funciona = false;}
                            }
                            break;
                        case EN_NORMAL:
                            if(this->GetModo() == MODO_DEFAULT)
                            {
                                funciona = true;
                            }
                            else {funciona = false;}
                            break;
                        case EN_PELIGRO:
                            if(this->GetModo() == MODO_PELIGRO)
                            {
                                funciona = true;
                            }
                            else {funciona = false;}
                            break;
                        case EN_ATAQUE_ESPECIAL:
                            if(this->getBarraAtEs() == constantes.CIEN)
                            {
                                funciona = true;
                            }
                            else {funciona = false;}
                            break;
                        default:
                            funciona = false;
                            break;
                    }
                }
                break;
            case EN_CAMBIAR:    //Cambia el modo del boss
                switch (_ordenes[1])
                {
                    case EN_PELIGRO:
                            this->SetModo(MODO_PELIGRO);
                        break;
                
                    default:
                            this->SetModo(MODO_DEFAULT);
                        break;
                }
            case EN_ATAQUE_ESPECIAL:    //El boss realiza uno de sus ataques especiales
                switch (_ordenes[1])
                {
                    case EN_AT_ESP_2:
                        setRespawnBoss(true);
                        /* Llamar animacion pedir ayuda */
                        break;
                
                    default:
                        /* ataque especial 1 */
                        break;
                }
            case EN_ATACAR: //El boss ataca
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
            case EN_MOVERSE: //El boss se mueve tanteando al jugador
                {
                    funciona = true;
                }
                break;
            case EN_DEFENDERSE: //El boss se defiende
                {
                    funciona = true;
                }
            default:
                break;
        }
    }
}

void MuerteBoss::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}
