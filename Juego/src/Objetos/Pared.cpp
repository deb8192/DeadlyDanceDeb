#include "Pared.hpp"
#include "../Motores/MotorFisicas.hpp"

Pared::Pared(int id, int codigo,
    int anc, int lar, int alt,
    float x, float y, float z, unsigned short tipoObj,
    float despX, float despZ, int accion)
: Interactuable(id, codigo, anc, lar, alt, 
    x, y, z, tipoObj, despX, despZ, accion)
{
    //_modelo = "assets/models/Pared.obj";
    //_textura = nullptr;
}

Pared::~Pared()
{
    //_modelo = nullptr;
    //_textura = nullptr;
}

void Pared::Borrar(unsigned short pos)
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->ErasePared(pos);
    _fisicas = nullptr;
    _motor->ErasePared(pos);
}