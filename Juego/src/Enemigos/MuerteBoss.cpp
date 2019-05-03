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
    direccion = 0;

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
    if(this->getTimeMoverse() <= 0)
    {
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
 *      i: sennala al enemigo del array
 * Salidas:
*/

void MuerteBoss::UpdateMuerteBoss(short *i, int* _jug, bool ayuda)
{
    Jugador* _jugador = (Jugador*)_jug;
    funciona = true;
    if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_COMPROBAR: //Comprueba distintas condiciones del enemigo como su vida
                {
                    switch (_ordenes[1])
                    {
                        case EN_MAX_VIDA_33:
                            {
                                int porcentaje_33 = this->getVidaIni() * constantes.MAX_VIDA_BOSS_PELIGRO / constantes.CIEN;
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
                    int nuevaDireccion = 0;
                    if(!hecho)
                    {
                        //Moverse estableciendo una direccion de movimiento 
                        nuevaDireccion = rand() % 8 + 1;       
                        direccion = this->Moverse(nuevaDireccion, direccion, _jug);
                        this->setTimeMoverse(1.5f);
                        hecho = true;
                    }
                    else
                    { 
                        //Se desplaza y cambia la direccion cada medio segundo de tiempo
                        if(this->getTimeMoverse() > 0)
                        {
                            float resto = (float) ((int) (this->getTimeMoverse() * constantes.CIEN) % (int) (constantes.UN_MEDIO * constantes.CIEN)) / constantes.CIEN;
                            if(resto <= constantes.DIEZ_PORCIENTO)
                            {
                                nuevaDireccion = rand() % 8 + 1;    
                                this->setTimeMoverse(this->getTimeMoverse() - resto);
                            }
                        }
                        direccion = this->Moverse(nuevaDireccion, direccion, _jug);
                    }
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
