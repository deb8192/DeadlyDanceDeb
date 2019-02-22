#include "TLuz.hpp"

TLuz::TLuz()
{
    didentidad = 'L'; //para sabe que funcion hace
}
       
TLuz::~TLuz()
{

}

void TLuz::setIntensidad(float *)
{

}

float TLuz::getIntensidad()
{
    return 0.0f;
}

void TLuz::beginDraw()
{
    std::cout << didentidad << " realizacion operacion de descolar" << std::endl;
    
}

void TLuz::endDraw()
{
    std::cout << didentidad << "final" << std::endl;
}