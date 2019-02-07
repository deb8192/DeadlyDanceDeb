#include "pollo.hpp"
#include "Nivel.hpp"

pollo::pollo() : Enemigo()
{
    funciona = true;
}

pollo::~pollo()
{

}

void pollo::runIA()
{
    int danyo;
    Nivel * nivel;
    int* ordenes = Enemigo::runIA(funciona);
    float x = Enemigo::getX();
    float y = Enemigo::getY();
    float z = Enemigo::getZ();
    
    struct Datos{
        float distancia = 5.0;
        float velocidadX = 0;
        float velocidadY = 0;
        float velocidadZ = 0;
    }datosDesplazamiento;
    switch (ordenes[0])
    {
        case 0:
            cout<<"Se Mueve"<<endl;
            nivel = Nivel::getInstance();
            if(nivel->GetJugador()->getX() > this->Enemigo::getX() + datosDesplazamiento.distancia)
            {
                x += this->Enemigo::getVelocidad();
                datosDesplazamiento.velocidadX += this->Enemigo::getVelocidad(); 
            }
            else if(nivel->GetJugador()->getX() < this->Enemigo::getX() - datosDesplazamiento.distancia)
            {
                x -= this->Enemigo::getVelocidad();
                datosDesplazamiento.velocidadX -= this->Enemigo::getVelocidad(); 
            }
            if(nivel->GetJugador()->getZ() > this->Enemigo::getZ() + datosDesplazamiento.distancia)
            {
                z += this->Enemigo::getVelocidad();
                datosDesplazamiento.velocidadZ += this->Enemigo::getVelocidad(); 
            }
            else if(nivel->GetJugador()->getZ() < this->Enemigo::getZ() - datosDesplazamiento.distancia)
            {
                z -= this->Enemigo::getVelocidad();
                datosDesplazamiento.velocidadZ -= this->Enemigo::getVelocidad(); 
            }
            this->Enemigo::setNewPosiciones(x, y, z);
            this->Enemigo::setPosicionesFisicas(datosDesplazamiento.velocidadX, datosDesplazamiento.velocidadY, datosDesplazamiento.velocidadZ);
            if(nivel->GetJugador()->getZ() <= this->Enemigo::getZ() + datosDesplazamiento.distancia || nivel->GetJugador()->getZ() >= this->Enemigo::getZ() - datosDesplazamiento.distancia)
            {
                if(nivel->GetJugador()->getX() <= this->Enemigo::getX() + datosDesplazamiento.distancia || nivel->GetJugador()->getX() >= this->Enemigo::getX() - datosDesplazamiento.distancia)
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
            break;
    
        case 1:
            danyo = this->Enemigo::Atacar();
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
            break;

        default:
            cout<<"No hace nada"<<endl;
            break;
    }
}
