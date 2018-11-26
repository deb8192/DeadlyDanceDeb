#include "Nodo.hpp"
#include <iostream>

using namespace std;

Hoja::Hoja(int idxml, int type, Nodo* father, const char* action, const char* target, const char* blackboard, int task, const char* information)
{
    id = idxml;
    tipo = type;
    padre = father;
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
int Hoja::getID()
{
    return id;
}
