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
    switch (ordenes[0])
    {
        case 0:
            cout<<"Se Mueve"<<endl;
            /*if(nivel->GetJugador()->getX() > this->Enemigo::getX() + 3 || nivel->GetJugador()->getX() < this->Enemigo::getX() - 3)
            else if(nivel->GetJugador()->getX() > this->Enemigo::getX() + 3 || nivel->GetJugador()->getX() < this->Enemigo::getX() - 3)
            if(nivel->GetJugador()->getZ() > this->Enemigo::getZ() + 3 || nivel->GetJugador()->getX() < this->Enemigo::getX() - 3)
            else if(nivel->GetJugador()->getZ() > this->Enemigo::getZ() + 3 || nivel->GetJugador()->getX() < this->Enemigo::getX() - 3)
*/
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
