#include "Palanca.hpp"

Palanca::Palanca(int codigo, const char* nombre, 
    int anc, int lar, int alt, int posicion, float x, float y, float z, unsigned short tipoObj)
: Interactuable(codigo, nombre, anc, lar, alt, posicion, x, y, z, tipoObj)
{
    _modelo = "assets/models/Palanca.obj";
}

Palanca::~Palanca()
{
    _modelo = nullptr;
}

void Palanca::CrearFisica()
{
    //
}

void Palanca::BorrarFisica()
{
    //
}