#include "Palanca.hpp"

Palanca::Palanca(int id, int codigo,
    int anc, int lar, int alt,
    float x, float y, float z, unsigned short tipoObj,
    float despX, float despZ, int accion)
: Interactuable(id, codigo, anc, lar, alt, 
    x, y, z, tipoObj, despX, despZ, accion)
{
    _modelo = "assets/models/Palanca.obj";
    _textura = nullptr;
}

Palanca::~Palanca()
{
    _modelo = nullptr;
    _textura = nullptr;
}
