#include "Pollo.hpp"
#include "../ConstantesComunes.hpp"
#include "../Personajes/Jugador.hpp"
#include "cmath"

Pollo::Pollo(float nX, float nY, float nZ, int maxVida)
: Enemigo(nX,nY,nZ,maxVida)
{
    funciona = true;
    atacado = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS;
    rotation = constantes.CERO;

    _modelo = "assets/models/Pollo.obj";
    _textura = "assets/texture/texturas_pollito.png";
}

Pollo::~Pollo()
{
    delete[] _ordenes;
    _ordenes = nullptr;
    _modelo = nullptr;
    _textura = nullptr;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del Pollo comportamiento en Enemigo
 *
 * Entradas:
 *
 * Salidas:
*/
void Pollo::RunIA()
{
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

/***************** UpdatePollo *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del pollo
 *
 * Entradas:
 *      i: (sennala al pollo del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/

void Pollo::UpdatePollo(short *i, int* _jug, bool ayuda)
{
    Jugador* _jugador = (Jugador*)_jug;
    funciona = true;
    if(modo == MODO_ATAQUE && _ordenes != nullptr)
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
            case EN_VER: //El Pollo ve al jugador
                {
                    if(this->ver(constantes.UNO, constantes.SEIS * constantes.CINCO))
                    {
                        this->ver(constantes.DOS, constantes.SEIS * constantes.CINCO);
                        if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                        {
                            funciona = true;
                        }
                        else
                        {
                            funciona = false;
                        }
                    }
                    else
                    {
                        funciona = false;
                    }
                }
                break;

                case EN_PIDE_AYUDA: //El Pollo pide ayuda
                {
                    modo = MODO_ATAQUE;
                    this->setTimeMerodear(constantes.CERO);
                    //cout<<"Pide ayuda a los aliados"<<endl;
                    this->PedirAyuda(ayuda);
                    funciona = true;
                }
                break;

                case EN_OIR: //El Pollo oye un enemigo pedir ayuda
                {
                    if(this->oir(constantes.DOS))
                    {
                        funciona = true;
                    }
                    else
                    {
                        funciona = false;
                    }
                }
                break;

                case EN_ACUDE_AYUDA: //El Pollo oye un enemigo pedir ayuda
                {
                    this->ContestarAyuda();
                }
                break;

            case EN_MERODEA: //El Pollo merodea
                {
                    this->ver(constantes.DOS, constantes.SEIS * constantes.CINCO);
                    if(!hecho)
                    {
                        //Merodea estableciendo un nuevo angulo de rotacion
                        this->setRotation(this->randomBinomial() * maxRotacion);
                        this->Merodear();
                        this->setTimeMerodear(1.5f);
                        hecho = true;
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO, constantes.SEIS * constantes.CINCO))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_ATAQUE;
                                this->setTimeMerodear(constantes.CERO);
                                //cout<<"Pide ayuda a los aliados"<<endl;
                                this->PedirAyuda(ayuda);
                                funciona = true;
                            }
                        }
                        else if(this->oir(constantes.DOS))
                        {
                            this->ContestarAyuda();
                        }
                    }
                    else
                    {
                        //Merodea poniendo en positivo o negativo el angulo actual de rotacion
                        int rota = rand() % 3 - 1;
                        if (rota != 0)
                        {
                            rotation *= rota;
                        }
                        this->Merodear();
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO, constantes.SEIS * constantes.CINCO))
                        {
                            if(distanciaEnemigoJugador.modulo < distanciaEnemigoObstaculo.modulo)
                            {
                                modo = MODO_ATAQUE;
                                this->setTimeMerodear(constantes.CERO);
                                //cout<<"Pide ayuda a los aliados"<<endl;
                                this->PedirAyuda(ayuda);
                                funciona = true;
                            }
                        }
                        else if(this->oir(constantes.DOS))
                        {
                            this->ContestarAyuda();
                        }
                    }
                    funciona = true;
                }
                break;

            default:
                break;
        }
    }
}

void Pollo::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}
