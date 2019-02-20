#include "Pollo.hpp"
#include "../Jugando/Jugando.hpp"
#include "cmath"

#define PIRADIAN 180.0f

Pollo::Pollo() : Enemigo()
{
    funciona = true;
    _ordenes = nullptr;
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
    _ordenes = Enemigo::RunIA(funciona);
}

void Pollo::UpdatePollo(int i)
{
    if(_ordenes != nullptr)
    {
        switch (_ordenes[0])
        {
            case 0: //El Pollo se mueve
                {
                    Jugando* _nivel;
                    bool trueX = false;
                    float x = this->Enemigo::getNewX();
                    float y = this->Enemigo::getNewY();
                    float z = this->Enemigo::getNewZ();
                    float rotacion = 0.0;
                    
                    struct Datos{
                        float distancia = 4.0;
                        float velocidadX = 0.0;
                        float velocidadY = 0.0;
                        float velocidadZ = 0.0;
                    }datosDesplazamiento;
                    
                    cout<<"Se mueve el Pollo"<<endl;
                    _nivel = Jugando::GetInstance();
                    if(_nivel->GetJugador()->getNewX() > this->Enemigo::getNewX() + datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = -90.0f;
                        datosDesplazamiento.velocidadX = this->Enemigo::getVelocidad(); 
                    }
                    else if(_nivel->GetJugador()->getNewX() < this->Enemigo::getNewX() - datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = 90.0f;
                        datosDesplazamiento.velocidadX = -this->Enemigo::getVelocidad(); 
                    }
                    if(_nivel->GetJugador()->getNewZ() > this->Enemigo::getNewZ() + datosDesplazamiento.distancia)
                    {
                        if(trueX)
                        {
                            if(rotacion > 0)
                                rotacion -= 45.0f;
                            else
                                rotacion += 45.0f;

                            datosDesplazamiento.velocidadZ = this->Enemigo::getVelocidad() * 0.5; 
                            datosDesplazamiento.velocidadX *= 0.5;
                        }
                        else
                        {
                            rotacion = 0.0f;
                            datosDesplazamiento.velocidadZ = this->Enemigo::getVelocidad(); 
                        }
                    }
                    else if(_nivel->GetJugador()->getNewZ() < this->Enemigo::getNewZ() - datosDesplazamiento.distancia)
                    {
                        if(trueX)
                        {
                            if(rotacion > 0)
                                rotacion += 45.0f;
                            else
                                rotacion -= 45.0f;
                            datosDesplazamiento.velocidadZ = -this->Enemigo::getVelocidad() * 0.5; 
                            datosDesplazamiento.velocidadX *= 0.5;
                        }
                        else
                        {
                            rotacion = 180.0f;
                            datosDesplazamiento.velocidadZ = -this->Enemigo::getVelocidad(); 
                        }
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
        
            case 1: //El Pollo ataca
                {
                    cout<<"intenta atacar"<<endl;
                    Jugando* _nivel;
                    int danyo;
                    danyo = this->Enemigo::Atacar(i);
                    _nivel = Jugando::GetInstance();
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

            default:
                cout<<"No hace nada"<<endl;
                break;
        }
    }
}
