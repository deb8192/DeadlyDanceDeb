#include "TEntidad.hpp"

glm::mat4* TEntidad::matriz_compartida = new glm::mat4;
std::stack<glm::mat4 *> * TEntidad::pila_compartida = new std::stack<glm::mat4 *>;