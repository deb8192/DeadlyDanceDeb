#include "Cofre.hpp"
//#include "../Motores/MotorFisicas.hpp"

Cofre::Cofre(bool esEne, int id,
    float x, float y, float z, unsigned short tipoObj,
    unsigned short posA, Sala* sala, unsigned short posFis)
: Interactuable(id, -1, 2, 4, 4, //codigo,ancho,largo,alto
    x, y, z, tipoObj, 0, 0, 0) // despX, despZ, accion
{
    esArana = esEne;
    _modelo = "assets/models/Cofre/cofre.obj";
    _textura = "assets/texture/cofreArana.png";
    _estoy = sala;
    posArrayArana = posA;
    
    // El array de cofres de jugando y fisicas estan en el mismo orden
    posFisCofre = posFis;
}

Cofre::~Cofre()
{
    _modelo = nullptr;
    _textura = nullptr;
    _estoy = nullptr;
    esArana=false;
    posArrayArana=0;
    posFisCofre = 0;
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

void Cofre::ActivarCofre()
{
    //TO DO:
    /*if (esArana)
        _fisicas->ActivarObstaculo(posObstaculos);
    _fisicas->ActivarCofre(pos);*/
}

void Cofre::DesactivarCofre()
{
    if (esArana)
        _fisicas->EraseObstaculo(posObstaculos);
    _fisicas->DesactivarCofre(posFisCofre);
}
