#include "Nodo.hpp"
#include <iostream>

using namespace std;
Hoja::Hoja()
{

}

Hoja::Hoja(const char* name, int idxml, int type, int level, Nodo* father, const char* action, const char* target, const char* blackboard, int task, const char* information) : Nodo(name, idxml, type, level, father)
{
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

const char* Hoja::GetAccion()
{
    return accion;
}

const char* Hoja::GetObjetivo()
{
    return objetivo;
}