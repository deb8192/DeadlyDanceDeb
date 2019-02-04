#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include "pugixml.hpp"
#include "Nodo.hpp"
#include "Arbol.hpp"

#include "Arbol2.hpp"
#include "hoja2.hpp"

#ifndef CargadorBehaviorTrees_HPP
#define CargadorBehaviorTrees_HPP

class CargadorBehaviorTrees
{
    public:
    	CargadorBehaviorTrees();
        ~CargadorBehaviorTrees();
        Arbol cargarBehaviorTreeXml(std::string);
        void guardarBehaviorTreeXml(std::string);

        Arbol2 * cargarArbol(std::string);

    private:
        const char* SELECTOR  = "selector";
    	const char* SEL_ALEATORIO  = "selector-aleatorio";
    	const char* SECUENCIA  = "secuencia";
    	const char* SEC_ALEATORIA  = "secuencia-aleatoria";
    	const char* TAREA  = "tarea";
    	const char* ITERATOR  = "iterador";
        const char* RAIZ = "Root";
        const char* COMPOSICION = "Composition";
        const char* DECORADOR = "Decorator";
        const char* HOJA = "Leaf";
        const char* PIZARRA = "Blackboard";
        const char* LEE = "lee";
        const char* ESCRIBE = "escribe";
        const char* VERDADERO = "true";
        const char* FALSO = "false";
        
        void generarTarea(pugi::xml_node, const char **, int, unsigned int, int);
        Nodo* anyadirHijo(Arbol*, Nodo*, Nodo*, int);
        Arbol CrearArbolComportamiento(vector <pugi::xml_node>, Nodo *, Nodo *, int);
        Composicion* raiz;
        int * lista;
        vector <Arbol> behavior_tree;

        void agregarHoja(pugi::xml_node rutapadre,hoja2 *, Arbol2 * arb);//recibe al padre por parametro
         
};
#endif