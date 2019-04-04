#include "Puerta.hpp"

Puerta::Puerta(int id, int codigo,
    int anc, int lar, int alt,
    float x, float y, float z, unsigned short tipoObj,
    float despX, float despZ, int accion)
: Interactuable(id, codigo, anc, lar, alt,
    x, y, z, tipoObj, despX, despZ, accion)
{
    if (tipoObj == 2)
        _modelo = "assets/models/Puertas/Puerta2.obj";
    else
        _modelo = "assets/models/Puertas/Puerta.obj";
    _textura = "assets/texture/Puerta.png";
}

Puerta::~Puerta()
{
    _modelo = nullptr;
    _textura = nullptr;
}

void Puerta::GirarPuerta(float rotacion)
{
    setNewRotacion(rotActual.x, rotActual.y + rotacion, rotActual.z);
    _fisicas->updatePuerta(posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y + rotacion, rotActual.z,
        _desplazamientos[0], _desplazamientos[1], posObstaculos);
}