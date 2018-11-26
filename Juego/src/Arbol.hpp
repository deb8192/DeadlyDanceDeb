#include <iostream>
#include "Nodo.hpp"

#ifndef Arbol_HPP
#define Arbol_HPP

using namespace std;

class Arbol
{
    public:
        Arbol(Nodo *, const char*);
    private:
        
        const char* nombre;
        Nodo *raiz;
};
#endif