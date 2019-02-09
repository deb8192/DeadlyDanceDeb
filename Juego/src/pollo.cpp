#include "pollo.hpp"
#include "Nivel.hpp"
#include "cmath"

#define PIRADIAN 180.0f

pollo::pollo() : Enemigo()
{
    funciona = true;
    ordenes = nullptr;
}

pollo::~pollo()
{

}

/***************** runIA *****************
 * Funcion que llama a recorrer el arbol
 * de del pollo comportamiento en Enemigo
 * 
 * Entradas:
 * 
 * Salidas:
*/
void pollo::runIA()
{
    ordenes = Enemigo::runIA(funciona);
}

void pollo::updatePollo(int i)
{
    if(ordenes != nullptr)
    {
        switch (ordenes[0])
        {
            case 0: //El pollo se mueve
                {
                    Nivel * nivel;
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
                    
                    cout<<"Se mueve el pollo"<<endl;
                    nivel = Nivel::getInstance();
                    if(nivel->GetJugador()->getNewX() > this->Enemigo::getNewX() + datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = -90.0f;
                        datosDesplazamiento.velocidadX = this->Enemigo::getVelocidad(); 
                    }
                    else if(nivel->GetJugador()->getNewX() < this->Enemigo::getNewX() - datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = 90.0f;
                        datosDesplazamiento.velocidadX = -this->Enemigo::getVelocidad(); 
                    }
                    if(nivel->GetJugador()->getNewZ() > this->Enemigo::getNewZ() + datosDesplazamiento.distancia)
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
                    else if(nivel->GetJugador()->getNewZ() < this->Enemigo::getNewZ() - datosDesplazamiento.distancia)
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
                    if(abs(nivel->GetJugador()->getZ() - this->Enemigo::getZ()) <= abs(datosDesplazamiento.distancia))
                    {
                        if(abs(nivel->GetJugador()->getX() - this->Enemigo::getX()) <= abs(datosDesplazamiento.distancia))
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
        
            case 1: //El pollo ataca
                {
                    cout<<"intenta atacar"<<endl;
                    Nivel * nivel;
                    int danyo;
                    danyo = this->Enemigo::Atacar(i);
                    nivel = Nivel::getInstance();
                    if(danyo > 0)
                    {
                        nivel->GetJugador()->QuitarVida(danyo);
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
