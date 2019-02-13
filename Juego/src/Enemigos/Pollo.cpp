#include "Pollo.hpp"
#include "../Jugando/Nivel.hpp"
#include "cmath"

#define PIRADIAN 180.0f

Pollo::Pollo() : Enemigo()
{
    funciona = true;
    atacado = false;
    _ordenes = nullptr;
}

Pollo::~Pollo()
{

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
    if(this->getTimeMerodear() == 0)
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

/***************** UpdatePollo *****************
 * Funcion que llama a la funcion actual donde se
 * ha quedado la lectura del arbol del pollo
 * 
 * Entradas:
 *      i: (sennala al pollo del array, NO NECESARIO APARENTEMENTE)
 * Salidas:
*/ 

void Pollo::UpdatePollo(int i)
{

    funciona = true;
    if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case MOVERSE: //El Pollo se mueve
                {
                    Nivel* _nivel;
                    bool trueX = false;
                    bool trueZ = false;
                    float x = this->getNewX();
                    float y = this->getNewY();
                    float z = this->getNewZ();
                    float rotacion = 0.0;
                    
                    //Struct para indicar la velocidad de desplazamiento y la
                    //distancia de los enemigos al jugador
                    struct Datos{
                        float distancia = 4.0;
                        float velocidadX = 0.0;
                        float velocidadY = 0.0;
                        float velocidadZ = 0.0;
                    }datosDesplazamiento;
                    
                    cout<<"Se mueve el Pollo"<<endl;
                    _nivel = Nivel::getInstance();

                    //Se mueve a la derecha
                    if(_nivel->GetJugador()->getNewX() > this->getNewX() + datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = 90.0f;
                        datosDesplazamiento.velocidadX = this->getVelocidad(); 
                    }

                    //Se mueve a la izquierda
                    else if(_nivel->GetJugador()->getNewX() < this->getNewX() - datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = -90.0f;
                        datosDesplazamiento.velocidadX = -this->getVelocidad(); 
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
                                rotacion -= 45.0f;
                            
                            //Se mueve hacia arriba a la derecha
                            else
                                rotacion += 45.0f;

                            datosDesplazamiento.velocidadZ = this->getVelocidad() * 0.5; 
                            datosDesplazamiento.velocidadX *= 0.5;
                        }

                        //Se mueve recto hacia arriba
                        else
                        {
                            rotacion = 0.0f;
                            datosDesplazamiento.velocidadZ = this->getVelocidad(); 
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
                                rotacion += 45.0f;

                            //Se mueve hacia abajo a la izquierda
                            else
                                rotacion -= 45.0f;
                            datosDesplazamiento.velocidadZ = -this->getVelocidad() * 0.5; 
                            datosDesplazamiento.velocidadX *= 0.5;
                        }

                        //Se mueve hacia abajo
                        else
                        {
                            rotacion = 180.0f;
                            datosDesplazamiento.velocidadZ = -this->getVelocidad(); 
                        }
                    }

                    if(!trueX && !trueZ)
                    {
                        rotacion = this->Enemigo::getRY();
                    }

                    x += datosDesplazamiento.velocidadX;
                    z += datosDesplazamiento.velocidadZ;
                    this->setNewRotacion(this->Enemigo::getRX(), rotacion, this->Enemigo::getRZ());
                    this->setNewPosiciones(x, y, z);
                    this->setPosicionesFisicas(datosDesplazamiento.velocidadX, datosDesplazamiento.velocidadY, datosDesplazamiento.velocidadZ);
                    
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
        
            case ATACAR: //El Pollo ataca
                {
                    if(!atacado)
                    {
                        cout<<"intenta atacar"<<endl;
                        Nivel* _nivel;
                        int danyo;
                        danyo = this->Atacar(i);
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
            
            case VER: //El Pollo ve al jugador
                {
                    short int jugador = 1;
                    cout<<"Comprueba si ve al jugador"<<endl;
                    if(this->ver(jugador))
                    {
                        funciona = true;
                    }
                    else 
                    {
                        funciona = false;
                    }
                }
                break;
            case PIDE_AYUDA: //El Pollo pide ayuda
                {
                    cout<<"Pide ayuda a los aliados"<<endl;
                    this->pedirAyuda();
                    funciona = true;
                }
                break;
            case MERODEA: //El Pollo merodea
                {
                    cout<<"Merodea"<<endl;
                    if(!hecho)
                    {
                        direccion = rand() % 8 + 0;
                        this->Merodear(direccion);
                        this->setTimeMerodear(1.5f);
                        hecho = true;
                    }
                    else 
                    {
                        this->Merodear(direccion);
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
