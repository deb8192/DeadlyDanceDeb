#include <iostream>
#include "Nodo.hpp"

#ifndef Arbol_HPP
#define Arbol_HPP

using namespace std;

class Arbol
{
    public:
        Arbol(Nodo *, const char*);
        Nodo* anyadirHijo(Nodo *);
    private:
        
        const char* nombre;
        Composicion *raiz;
};
#endif