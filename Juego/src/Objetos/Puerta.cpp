#include "Puerta.hpp"

Puerta::Puerta(int codigo, const char* nombre,
    int anc, int lar, int alt, int posicion, float x, float y, float z, unsigned short tipoObj)
: Interactuable(codigo, nombre, anc, lar, alt, posicion, x, y, z, tipoObj)
{
    if (tipoObj == 2)
    {
        _modelo = "assets/models/Puerta2.obj";
        _textura = "assets/texture/Puerta.png";
    }
    else
    {
        _modelo = "assets/models/Puerta.obj";
        _textura = "assets/texture/Puerta.png";
    }
}

Puerta::~Puerta()
{
    _modelo = nullptr;
    _textura = nullptr;
}

void Puerta::CrearFisica()
{
    //
}

void Puerta::BorrarFisica()
{
    //
}

// TO DO: al cargarlas pasarle la rotacion por defecto para que se puedan reiniciar
