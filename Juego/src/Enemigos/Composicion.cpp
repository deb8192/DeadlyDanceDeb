#include "../Nodo.hpp"
#include <iostream>

using namespace std;
Composicion::Composicion()
{

}

Composicion::Composicion(const char* name, int idxml, int type, int level, Nodo *father, const char* action, const char* target, const char* blackboard, int task, const char* information, bool random) : Nodo(name, idxml, type, level, father)
{
    
    aleatorio = random;

    std::string actionComp(action);
    char * cadena_accion = new char[sizeof(actionComp)];
    strcpy(cadena_accion, actionComp.c_str());

    std::string targetComp(target);
    char * cadena_objetivo = new char[sizeof(targetComp)];
    strcpy(cadena_objetivo, targetComp.c_str());

    accion = cadena_accion;
    objetivo = cadena_objetivo;
    if(std::strcmp(blackboard, "true") == 0)
    {

        std::string tareaInfo(information);
        char * cadena_info = new char[sizeof(tareaInfo)];
        strcpy(cadena_info, tareaInfo.c_str());

        pizarra = true;
        tarea = task;
        info = cadena_info;
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

const char* Composicion::GetAccion()
{
    return accion;
}

const char* Composicion::GetObjetivo()
{
    return objetivo;
}
