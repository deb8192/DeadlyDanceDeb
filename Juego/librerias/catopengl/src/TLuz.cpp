#include "TLuz.hpp"

TLuz::TLuz()
{
    didentidad = 'L'; //para sabe que funcion hace
}
       
TLuz::~TLuz()
{

}

void TLuz::remove()
{
    this->~TLuz();
}

void TLuz::setIntensidad(float *)
{

}

float * TLuz::getIntensidad()
{

}

void TLuz::beginDraw()
{
    std::cout << didentidad << " se debe pintar-> " << ejecucion << std::endl;
}

void TLuz::endDraw()
{
    std::cout << didentidad << "final" << std::endl;
}