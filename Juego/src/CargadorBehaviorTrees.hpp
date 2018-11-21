#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "Nodo.hpp"

#ifndef CargadorBehaviorTrees_HPP
#define CargadorBehaviorTrees_HPP

class CargadorBehaviorTrees
{
    public:
        void cargadorBehaviorTrees();
        void cargarBehaviorTreeXml(std::string);
        void guardarBehaviorTreeXml(std::string);

    private:
        int * lista; 
        Nodo *nodo;
         
};

#endif