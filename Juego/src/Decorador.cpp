#include "Nodo.hpp"
#include <iostream>

using namespace std;

Decorador::Decorador(int idxml, int type, Nodo *father, const char* end, const char* alternative)
{
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
