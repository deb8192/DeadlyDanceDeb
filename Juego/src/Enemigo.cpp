#include "Enemigo.hpp"

Enemigo::Enemigo()
{
    
}

void Enemigo::definirSala(Sala * sala)
{
    estoy = sala;
}

Sala* Enemigo::getSala()
{
    return estoy;
}
