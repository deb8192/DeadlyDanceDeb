#include "TEntidad.hpp"

glm::mat4* TEntidad::matriz_compartida = new glm::mat4;
std::stack<glm::mat4 *> * TEntidad::pila_compartida = new std::stack<glm::mat4 *>;

void TEntidad::NoEjecutar()
{
    ejecucion  = false;
}

void TEntidad::Ejecutar()
{
    ejecucion  = true;
}

bool TEntidad::GetEjecutar()
{
    return ejecucion;
}