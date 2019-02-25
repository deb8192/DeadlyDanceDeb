#include "Murcielago.hpp"
#include "../ConstantesComunes.hpp"
#include "../Jugando/Nivel.hpp"
#include "cmath"

Murcielago::Murcielago() : Enemigo()
{
    Constantes constantes;
    funciona = true;
    atacado = false;
    _ordenes = new short [constantes.DOS];
    maxRotacion = constantes.PI_CUARTOS; 
    rotation = constantes.CERO;
}

Murcielago::~Murcielago()
{
    Constantes constantes;
    funciona = false;
    atacado = false;
    for(short i = 0; i < constantes.DOS; i++)
    {
        _ordenes[i] = 0;
    }
    delete _ordenes;
    maxRotacion = 0;
    rotation = 0.0f;
}

/***************** RunIA *****************
 * Funcion que llama a recorrer el arbol
 * de del Murcielago comportamiento en Enemigo
 * 
 * Entradas:
 * 
 * Salidas:
*/
void Murcielago::RunIA()
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

/***************** UpdateMurcielago *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del Murcielago
 * 
 * Entradas:
 *      i: (sennala al Murcielago del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/ 

void Murcielago::UpdateMurcielago(short *i)
{
    Constantes constantes;

    funciona = true;
    if(modo == constantes.UNO && _ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case EN_PERSIGUE: //El Murcielago se mueve
                {
                    Nivel* _nivel;
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
                    
                    cout<<"Se mueve el Murcielago"<<endl;
                    _nivel = Nivel::getInstance();

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

                        //Se mueve recto hacia arriba
                        else
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

                        //Se mueve hacia abajo
                        else
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
        
            case EN_ATACAR: //El Murcielago ataca
                {
                    if(!atacado)
                    {
                        cout<<"intenta atacar"<<endl;
                        Nivel* _nivel;
                        int danyo;
                        danyo = this->Atacar(*i);
                        _nivel = Nivel::getInstance();
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
            case EN_OIR: //El Murcielago oye al jugador
                {
                    if(this->oir(constantes.UNO))
                    {
                        funciona = true;
                    }
                    else 
                    {
                        funciona = false;
                    }
                }
                break;
            case EN_PIDE_AYUDA: //El Murcielago pide ayuda
                {
                    modo = MODO_ATAQUE;
                    this->setTimeMerodear(constantes.CERO);
                    cout<<"Pide ayuda a los aliados"<<endl;
                    this->pedirAyuda();
                    funciona = true;
                }
                break;
            case EN_MERODEA: //El Murcielago merodea
                {
                    if(!hecho)
                    {
                        //Merodea estableciendo un nuevo angulo de rotacion
                        this->setRotation(this->randomBinomial() * maxRotacion);
                        this->Merodear();
                        this->setTimeMerodear(1.5f);
                        hecho = true;
                        //Comprueba si ve al jugador para atacarle en caso necesario
                        if(this->oir(constantes.UNO))
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

void Murcielago::SetNuevasOrdenes(short newOrden)
{
    _ordenes[0] = newOrden;
}
