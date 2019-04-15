#include "ReyPollo.hpp"

ReyPollo::ReyPollo(float nX, float nY, float nZ, int maxVida)
: Enemigo(nX,nY,nZ,maxVida)
{
    _modelo = "assets/models/Pollo.obj";
    _textura = "assets/texture/texturas_pollito.png";
}

ReyPollo::~ReyPollo()
{
    _modelo = nullptr;
    _textura = nullptr;
}
