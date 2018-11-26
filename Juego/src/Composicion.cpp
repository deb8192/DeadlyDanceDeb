#include "Nodo.hpp"
#include <iostream>

using namespace std;

Composicion::Composicion(int idxml, int type, Nodo *father)
{
    id = idxml;
    tipo = type;
    padre = father;
}

/*void Composicion::addHijo(Nodo* hijo)
{
    hijos.push_back(*hijo);
}*/

int Composicion::getID()
{
    return id;
}