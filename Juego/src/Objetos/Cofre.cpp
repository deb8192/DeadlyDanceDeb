#include "Cofre.hpp"

Cofre::Cofre(bool esEne, int codigo, const char* nombre, 
    int anc, int lar, int alt, int posicion, float x, 
    float y, float z, unsigned short tipoObj, Sala* sala)
: Interactuable(codigo, nombre, anc, lar, alt, posicion, x, y, z, tipoObj)
{
    esArana = esEne;
    _modelo = "assets/models/Cofre/cofre.obj";
    _estoy = sala;
}

Cofre::~Cofre()
{
    _modelo = nullptr;
    _estoy = nullptr;
}

bool Cofre::GetEsArana()
{
    return esArana;
}

Sala* Cofre::GetSala()
{
    return _estoy;
}