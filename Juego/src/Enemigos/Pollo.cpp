#include "Pollo.hpp"
#include "../ConstantesComunes.hpp"
#include "cmath"

Pollo::Pollo() : Enemigo()
{
    _nivel = Jugando::GetInstance();
    Constantes constantes;
    funciona = true;
    atacado = false;
    _ordenes = nullptr;
    maxRotacion = constantes.PI_CUARTOS; 
    rotation = constantes.CERO;
}

Pollo::~Pollo()
{
    funciona = false;
    _ordenes = nullptr;
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
    Constantes constantes;
    if(this->getTimeMerodear() <= 0)
    {
        if(modo == constantes.UNO)
        {
            if(_ordenes[0] != EN_MOVERSE && _ordenes[0] != EN_ATACAR)
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

void Pollo::UpdatePollo(short *i)
{
    Constantes constantes;
    funciona = true;
    if(modo == constantes.UNO && _ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_MOVERSE: //El Pollo se mueve
                {
                    bool trueX = false;
                    bool trueZ = false;
                    float x = this->getNewX();
                    float y = this->getNewY();
                    float z = this->getNewZ();
                    float rotacion = constantes.CERO;

                    //Struct para indicar la velocidad de desplazamiento y la
                    //distancia de los enemigos al jugador
                    struct Datos{
                        float distancia = 4.0;
                        float velocidadX = 0.0;
                        float velocidadY = 0.0;
                        float velocidadZ = 0.0;
                    }datosDesplazamiento;
                    
                    cout<<"Se mueve el Pollo"<<endl;
                    
                    //Se mueve a la derecha
                    if(_nivel->GetJugador()->getNewX() > this->getNewX() + datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = constantes.PI_MEDIOS;
                        //datosDesplazamiento.velocidadX = this->getVelocidadMaxima();  
                    }
                    //Se mueve a la izquierda
                    else if(_nivel->GetJugador()->getNewX() < this->getNewX() - datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = -constantes.PI_MEDIOS;
                    }

                    //Se mueve hacia arriba
                    if(_nivel->GetJugador()->getNewZ() > this->getNewZ() + datosDesplazamiento.distancia)
                    {
                        trueZ = true;
                        //Desplazamiento en diagonal
                        if(trueX)
                        {
                            //Se mueve hacia arriba a la derecha
                            if(rotacion > 0)
                                rotacion -= constantes.PI_CUARTOS;
                            //Se mueve hacia arriba a la derecha
                            else
                                rotacion += constantes.PI_CUARTOS;
                        }
                        else //Se mueve recto hacia arriba
                        {
                            rotacion = constantes.CERO;
                        }
                    }
                    else if(_nivel->GetJugador()->getNewZ() < this->getNewZ() - datosDesplazamiento.distancia)
                    {
                        trueZ = true;
                        //Desplazamiento en diagonal
                        if(trueX)
                        {
                            //Se mueve hacia abajo a la derecha
                            if(rotacion > 0)
                                rotacion += constantes.PI_CUARTOS;
                            //Se mueve hacia abajo a la izquierda
                            else
                                rotacion -= constantes.PI_CUARTOS;
                        }
                        else //Se mueve hacia abajo
                        {
                            rotacion = constantes.PI_RADIAN;
                        }
                    }

                    if(trueX || trueZ)
                    {
                        this->Enemigo::setNewRotacion(this->Enemigo::getRX(), rotacion, this->Enemigo::getRZ());
                    }
                    this->setVectorOrientacion();
                    datosDesplazamiento.velocidadX = vectorOrientacion.vX * velocidadMaxima;
                    datosDesplazamiento.velocidadZ = vectorOrientacion.vZ * velocidadMaxima;

                    x += datosDesplazamiento.velocidadX;
                    z += datosDesplazamiento.velocidadZ;
                    this->setNewPosiciones(x, y, z);
                    this->setPosicionesFisicas(datosDesplazamiento.velocidadX, 0.0f, datosDesplazamiento.velocidadZ);

                    //Se comprueba si la distancia entre el enemigo y el jugador es menor o igual a la distancia maxima que que indica la variable "distancia"
                    if(abs(_nivel->GetJugador()->getZ() - this->getZ()) <= abs(datosDesplazamiento.distancia))
                    {
                        if(abs(_nivel->GetJugador()->getX() - this->getX()) <= abs(datosDesplazamiento.distancia))
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
        
            case EN_ATACAR: //El Pollo ataca
                {
                    if(!atacado)
                    {
                        cout<<"intenta atacar"<<endl;
                        int danyo;
                        danyo = this->Atacar(*i);
                        
                        if(danyo > 0)
                        {
                            _nivel->GetJugador()->QuitarVida(danyo);
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

                case EN_PIDE_AYUDA: //El Pollo pide ayuda
                {
                    modo = MODO_ATAQUE;
                    this->setTimeMerodear(constantes.CERO);
                    cout<<"Pide ayuda a los aliados"<<endl;
                    this->pedirAyuda();
                    funciona = true;
                }
                break;
            case EN_MERODEA: //El Pollo merodea
                {
                    if(!hecho)
                    {
                        //Merodea estableciendo un nuevo angulo de rotacion
                        this->setRotation(this->randomBinomial() * maxRotacion);
                        this->Merodear();
                        this->setTimeMerodear(1.5f);
                        hecho = true;
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->ver(constantes.UNO))
                        {
                            modo = MODO_ATAQUE;
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

void Pollo::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}