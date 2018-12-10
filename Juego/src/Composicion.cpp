#include "Nodo.hpp"
#include <iostream>

using namespace std;

Composicion::Composicion(const char* name, int idxml, int type, int level, Nodo *father, const char* action, const char* target, const char* blackboard, int task, const char* information, bool random) : Nodo(name, idxml, type, level, father)
{
    
    aleatorio = random;
    accion = action;
    objetivo = target;
    if(std::strcmp(blackboard, "true") == 0)
    {
        pizarra = true;
        tarea = task;
        info = information;
    }
    else
    {
        pizarra = false;
        tarea = 0;
        info = "";
    }
}

void Composicion::addHijo(Nodo* hijo)
{
    hijos.push_back(hijo);
}
vector <Nodo*> Composicion::getHijos()
{
    return hijos;
}
bool Composicion::getAleatorio()
{
    return aleatorio;
}
