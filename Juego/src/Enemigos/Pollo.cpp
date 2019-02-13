#include "Pollo.hpp"
#include "../Jugando/Nivel.hpp"
#include "cmath"

#define PIRADIAN 180.0f

Pollo::Pollo() : Enemigo()
{
    funciona = true;
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
    _ordenes = Enemigo::RunIA(funciona);
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
                    float x = this->Enemigo::getNewX();
                    float y = this->Enemigo::getNewY();
                    float z = this->Enemigo::getNewZ();
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
                    if(_nivel->GetJugador()->getNewX() > this->Enemigo::getNewX() + datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = 90.0f;
                        datosDesplazamiento.velocidadX = this->Enemigo::getVelocidad(); 
                    }

                    //Se mueve a la izquierda
                    else if(_nivel->GetJugador()->getNewX() < this->Enemigo::getNewX() - datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = -90.0f;
                        datosDesplazamiento.velocidadX = -this->Enemigo::getVelocidad(); 
                    }

                    //Se mueve hacia arriba
                    if(_nivel->GetJugador()->getNewZ() > this->Enemigo::getNewZ() + datosDesplazamiento.distancia)
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

                            datosDesplazamiento.velocidadZ = this->Enemigo::getVelocidad() * 0.5; 
                            datosDesplazamiento.velocidadX *= 0.5;
                        }

                        //Se mueve recto hacia arriba
                        else
                        {
                            rotacion = 0.0f;
                            datosDesplazamiento.velocidadZ = this->Enemigo::getVelocidad(); 
                        }
                    }
                    else if(_nivel->GetJugador()->getNewZ() < this->Enemigo::getNewZ() - datosDesplazamiento.distancia)
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
                            datosDesplazamiento.velocidadZ = -this->Enemigo::getVelocidad() * 0.5; 
                            datosDesplazamiento.velocidadX *= 0.5;
                        }

                        //Se mueve hacia abajo
                        else
                        {
                            rotacion = 180.0f;
                            datosDesplazamiento.velocidadZ = -this->Enemigo::getVelocidad(); 
                        }
                    }

                    if(!trueX && !trueZ)
                    {
                        rotacion = this->Enemigo::getRY();
                    }

                    x += datosDesplazamiento.velocidadX;
                    z += datosDesplazamiento.velocidadZ;
                    this->Enemigo::setNewRotacion(this->Enemigo::getRX(), rotacion, this->Enemigo::getRZ());
                    this->Enemigo::setNewPosiciones(x, y, z);
                    this->Enemigo::setPosicionesFisicas(datosDesplazamiento.velocidadX, datosDesplazamiento.velocidadY, datosDesplazamiento.velocidadZ);
                    
                    //Se comprueba si la distancia entre el enemigo y el jugador es menor o igual a la distancia maxima que que indica la variable "distancia"
                    if(abs(_nivel->GetJugador()->getZ() - this->Enemigo::getZ()) <= abs(datosDesplazamiento.distancia))
                    {
                        if(abs(_nivel->GetJugador()->getX() - this->Enemigo::getX()) <= abs(datosDesplazamiento.distancia))
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
                    cout<<"intenta atacar"<<endl;
                    Nivel* _nivel;
                    int danyo;
                    danyo = this->Enemigo::Atacar(i);
                    _nivel = Nivel::getInstance();
                    if(danyo > 0)
                    {
                        _nivel->GetJugador()->QuitarVida(danyo);
                        cout<<"Ataca por la IA" <<endl;
                        funciona = true;
                    }
                    else 
                    {
                        funciona = false;
                    }
                }
                break;
            
            case VER: //El Pollo ve al jugador
                {
                    short int jugador = 1;
                    cout<<"Comprueba si ve al jugador"<<endl;
                    if(this->Enemigo::ver(jugador))
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
                    this->Enemigo::pedirAyuda();
                    funciona = true;
                }
                break;

            default:
                cout<<"No hace nada"<<endl;
                break;
        }
    }
}
