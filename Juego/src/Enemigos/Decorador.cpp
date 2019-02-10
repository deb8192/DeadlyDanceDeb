#include "../Nodo.hpp"
#include <iostream>

using namespace std;

Decorador::Decorador()
{
    
}

Decorador::Decorador(const char* name, int idxml, int type, int level, Nodo *father, const char* end, const char* alternative) : Nodo(name, idxml, type, level, father)
{
    std::string finalDec(end);
    char * cadena_fin = new char[sizeof(finalDec)];
    strcpy(cadena_fin, finalDec.c_str());

    std::string finalAlt(alternative);
    char * cadena_alt = new char[sizeof(finalAlt)];
    strcpy(cadena_alt, finalAlt.c_str());

    fin = cadena_fin;
    alternativa = cadena_alt;
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