#include "Nodo.hpp"
#include <iostream>

using namespace std;
Nodo::Nodo()
{

}

Nodo::Nodo(const char* name, int idxml, int type, int level, Nodo* father)
{
    std::string name_nombre(name);
    char *cadena_nombre = new char[sizeof(name_nombre)];
    strcpy(cadena_nombre, name_nombre.c_str());

    nombre = cadena_nombre;
    id = idxml;
    tipo = type;
    padre = father;
    nivel = level;
}

Nodo::~Nodo()
{
    nombre = "";
    id = 0;
    tipo = 0;
    nivel = 0;
    delete padre;
    padre = NULL;
}

Nodo* Nodo::getPadre()
{
    return padre;
}
int Nodo::getNivel()
{
    return nivel;
}
int Nodo::getID()
{
    return id;
}
const char* Nodo::getNombre()
{
    return nombre;
}
int Nodo::getTipo()
{
    return tipo;
}
