#include "Puerta.hpp"

Puerta::Puerta(int codigo, const char* nombre, 
    int anc, int lar, int alt, int posicion, float x, float y, float z, unsigned short tipoObj)
: Interactuable(codigo, nombre, anc, lar, alt, posicion, x, y, z, tipoObj)
{
    if (tipoObj == 2)
        _modelo = "assets/models/Puerta2.obj";
    else
        _modelo = "assets/models/Puerta.obj";
}

Puerta::~Puerta()
{
    _modelo = nullptr;
}