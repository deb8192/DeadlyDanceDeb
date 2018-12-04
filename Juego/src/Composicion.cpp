#include "Nodo.hpp"
#include <iostream>

using namespace std;

Composicion::Composicion(const char* name, int idxml, int type, Nodo *father)
{
    nombre = name;
    id = idxml;
    tipo = type;
    padre = father;
}

void Composicion::addHijo(Nodo* hijo)
{
    hijos.push_back(*hijo);
}

int Composicion::getID()
{
    return id;
}
const char* Composicion::getNombre()
{
    return nombre;
}