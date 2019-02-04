#include "TTransform.hpp"

 
TTransform::TTransform()
{
    didentidad = 'T'; //para sabe que funcion hace
}

TTransform::~TTransform()
{

}

void TTransform::remove()
{
    this->~TTransform();
}

void TTransform::identidad()
{

}

void TTransform::cargar(float *)
{

}

void TTransform::trasponer()
{
    
}

void TTransform::invertir()
{

}

void TTransform::multiplicarVector(float *)
{

}

void TTransform::multiplicarMatriz(float *)
{
    
}

void TTransform::trasladar(float,float,float)
{

}

void TTransform::rotar(float,float,float,float)
{

}

void TTransform::escalar(float,float,float)
{

}

void TTransform::beginDraw()
{
    std::cout << didentidad << std::endl;
}

void TTransform::endDraw()
{

}