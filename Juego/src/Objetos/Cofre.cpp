#include "Cofre.hpp"
#include "../Motores/MotorFisicas.hpp"

Cofre::Cofre(bool esEne, int codigo, const char* nombre,
    int anc, int lar, int alt, int posicion,
    float x, float y, float z, unsigned short tipoObj,
    unsigned short posA, Sala* sala)
: Interactuable(codigo, nombre, anc, lar, alt, posicion, x, y, z, tipoObj)
{
    esArana = esEne;
    _modelo = "assets/models/Cofre/cofre.obj";
    _textura = "assets/texture/cofreArana.png";
    _estoy = sala;
    posArrayArana = posA;
}

Cofre::~Cofre()
{
    _modelo = nullptr;
    _estoy = nullptr;
    esArana=false;
    posArrayArana=0;
    //posArrayFisicas
}

bool Cofre::GetEsArana()
{
    return esArana;
}

Sala* Cofre::GetSala()
{
    return _estoy;
}

unsigned short Cofre::GetPosArray()
{
    return posArrayArana;
}

void Cofre::CrearFisica()
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    posArrayFisicas = _fisicas->crearCuerpoCofre(
        posActual.x/2,posActual.y/2,posActual.z/2,
        2,4,2, // ancho, alto, largo
        0,0); // despX, despZ
    _fisicas = nullptr;
}

void Cofre::BorrarFisica()
{
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->EraseCofre(posArrayFisicas[0],posArrayFisicas[1]);
    _fisicas = nullptr;
}
