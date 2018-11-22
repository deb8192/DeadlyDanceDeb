#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "pugixml.hpp"
#include "Nodo.hpp"

#ifndef CargadorBehaviorTrees_HPP
#define CargadorBehaviorTrees_HPP

class CargadorBehaviorTrees
{
    public:
    	const std::string SELECTOR  = "selector";
    	const std::string SEL_ALEATORIO  = "selector-aleatorio";
    	const std::string SECUENCIA  = "secuencia";
    	const std::string SEC_ALEATORIA  = "secuencia-aleatoria";
    	const std::string TAREA  = "tarea";
    	const std::string ITERATOR  = "iterador";


        void cargadorBehaviorTrees();
        void cargarBehaviorTreeXml(std::string);
        void guardarBehaviorTreeXml(std::string);

    private:
        pugi::xml_node sacarNodo(pugi::xml_node, int);
        int * lista; 
        Nodo *nodo;
         
};

#endif