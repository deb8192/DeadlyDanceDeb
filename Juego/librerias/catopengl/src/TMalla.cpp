#include "TMalla.hpp"

//constructor y destructor
TMalla::TMalla()
{
    didentidad = 'M'; //para sabe que funcion hace es informativo
}

TMalla::~TMalla()
{

}

void TMalla::remove()
{
    this->~TMalla();
}

// Propiedades 
void TMalla::cargarMalla()
{

}

// sobrecarga metodos TEntidad
void TMalla::beginDraw()
{
    std::cout << didentidad << " se debe pintar-> " << ejecucion << std::endl;
}

void TMalla::endDraw()
{

}