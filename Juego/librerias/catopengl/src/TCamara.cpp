#include "TCamara.hpp"

//constructor y destructor
TCamara::TCamara()
{
    didentidad = 'C'; //para sabe que funcion hace
}

TCamara::~TCamara()
{

}
        
void TCamara::remove()
{
    this->~TCamara();
}

//gestion de propiedades
void TCamara::setPerspectiva()
{

}

void TCamara::setParalela()
{

}

void TCamara::beginDraw()
{
    std::cout << didentidad << " se debe pintar-> " << ejecucion << std::endl;
}

void TCamara::endDraw()
{

}
