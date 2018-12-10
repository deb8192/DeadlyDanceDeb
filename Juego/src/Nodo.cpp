#include "Nodo.hpp"
#include <iostream>

using namespace std;

Nodo::Nodo(const char* name, int idxml, int type, int level, Nodo* father)
{
    nombre = name;
    id = idxml;
    tipo = type;
    padre = father;
    nivel = level;
}
Nodo* Nodo::getPadre()
{
    return padre;
}
int Nodo::getNivel()
{
    return nivel;
}
int Nodo::getID()
{
    return id;
}
const char* Nodo::getNombre()
{
    return nombre;
}
int Nodo::getTipo()
{
    return tipo;
}
