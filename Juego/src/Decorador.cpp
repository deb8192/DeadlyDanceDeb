#include "Nodo.hpp"
#include <iostream>

using namespace std;

Decorador::Decorador()
{
    
}

Decorador::Decorador(const char* name, int idxml, int type, int level, Nodo *father, const char* end, const char* alternative) : Nodo(name, idxml, type, level, father)
{
    fin = end;
    alternativa = alternative;
}

void Decorador::addHijo(Nodo* hijo)
{
    hijos.push_back(hijo);
}

vector <Nodo*> Decorador::getHijos()
{
    return hijos;
}

const char* Decorador::GetFin()
{
    return fin;
}

const char* Decorador::GetAlternativa()
{
    return alternativa;
}