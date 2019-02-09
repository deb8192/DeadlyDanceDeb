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
                    float x = Enemigo::getX();
                    float y = Enemigo::getY();
                    float z = Enemigo::getZ();
                    float ax = 0;
                    float az = 0;
                    float rotacion = 0.0;
                    float deg = 0.0f;
                    
                    struct Datos{
                        float distancia = 3.0;
                        float velocidadX = 0.0;
                        float velocidadY = 0.0;
                        float velocidadZ = 0.0;
                    }datosDesplazamiento;
                    cout<<"Se mueve el pollo"<<endl;
                    nivel = Nivel::getInstance();
                    if(nivel->GetJugador()->getX() > this->Enemigo::getX() + datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = -90.0f;
                        ax = 50;
                        //x += this->Enemigo::getVelocidad();
                        datosDesplazamiento.velocidadX = this->Enemigo::getVelocidad(); 
                    }
                    else if(nivel->GetJugador()->getX() < this->Enemigo::getX() - datosDesplazamiento.distancia)
                    {
                        trueX = true;
                        rotacion = 90.0f;
                        ax = -50;
                        //x -= this->Enemigo::getVelocidad();
                        datosDesplazamiento.velocidadX = -this->Enemigo::getVelocidad(); 
                    }
                    if(nivel->GetJugador()->getZ() > this->Enemigo::getZ() + datosDesplazamiento.distancia)
                    {
                        if(trueX)
                        {
                            if(rotacion > 0)
                                rotacion -= 45.0f;
                            else
                                rotacion += 45.0f;
                        }
                        else
                        {
                            rotacion = 0.0f;
                        }
                        az = 50;
                        //z += this->Enemigo::getVelocidad();
                        datosDesplazamiento.velocidadZ = this->Enemigo::getVelocidad(); 
                    }
                    else if(nivel->GetJugador()->getZ() < this->Enemigo::getZ() - datosDesplazamiento.distancia)
                    {
                        if(trueX)
                        {
                            if(rotacion > 0)
                                rotacion += 45.0f;
                            else
                                rotacion -= 45.0f;
                        }
                        else
                        {
                            rotacion = 180.0f;
                        }
                        az = -50;
                        //z -= this->Enemigo::getVelocidad();
                        datosDesplazamiento.velocidadZ = -this->Enemigo::getVelocidad(); 
                    }
                    //MCD para hacer bien el giro
                    float div = (float)__gcd((int)abs(ax),(int)abs(az));

                    if(div != 1.0 && div != 0.0)
                    {
                        ax /= div;
                        az /= div;
                    }

                    //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
                    az < 0 ?
                        deg = PIRADIAN + (RADTODEG * atan(ax/az)) :
                        deg =  RADTODEG * atan(ax/az) ;

                    x += datosDesplazamiento.velocidadX*sin(deg*DEGTORAD);
                    z += datosDesplazamiento.velocidadZ*cos(deg*DEGTORAD);


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
