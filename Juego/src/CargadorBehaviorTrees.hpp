#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "pugixml.hpp"
#include "Nodo.hpp"
#include "Arbol.hpp"

#ifndef CargadorBehaviorTrees_HPP
#define CargadorBehaviorTrees_HPP

class CargadorBehaviorTrees
{
    public:
    	const char* SELECTOR  = "selector";
    	const char* SEL_ALEATORIO  = "selector-aleatorio";
    	const char* SECUENCIA  = "secuencia";
    	const char* SEC_ALEATORIA  = "secuencia-aleatoria";
    	const char* TAREA  = "tarea";
    	const char* ITERATOR  = "iterador";


        CargadorBehaviorTrees();
        void cargarBehaviorTreeXml(std::string);
        void guardarBehaviorTreeXml(std::string);

    private:
        pugi::xml_node sacarNodo(pugi::xml_node, Nodo *, Nodo *);
        int * lista;
        Arbol *behavior_tree;
         
};
#endif