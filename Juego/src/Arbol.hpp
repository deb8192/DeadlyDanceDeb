#include <iostream>
#include "Nodo.hpp"

#ifndef Arbol_HPP
#define Arbol_HPP

using namespace std;

class Arbol
{
    public:
        Arbol(Nodo, string);
    private:
        
        string nombre;
        Nodo raiz;
};
#endif