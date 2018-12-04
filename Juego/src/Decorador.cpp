#include "Nodo.hpp"
#include <iostream>

using namespace std;

Decorador::Decorador(const char* name, int idxml, int type, Nodo *father, const char* end, const char* alternative)
{
    nombre = name;
    id = idxml;
    tipo = type;
    padre = father;
    fin = end;
    alternativa = alternative;
}

void Decorador::addHijo(Nodo* hijo)
{
    hijos.push_back(*hijo);
}

int Decorador::getID()
{
    return id;
}
const char* Decorador::getNombre()
{
    return nombre;
}
