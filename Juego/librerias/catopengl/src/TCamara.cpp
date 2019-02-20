#include "TCamara.hpp"

//constructor y destructor
TCamara::TCamara()
{
    didentidad = 'C'; //para sabe que funcion hace
}

TCamara::~TCamara()
{

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
    std::cout << didentidad << " se debe pintar-> " << pila_compartida->size() << std::endl;
}

void TCamara::endDraw()
{

}
