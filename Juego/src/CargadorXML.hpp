#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "pugixml.hpp"
//#include "Nodo.hpp"
//#include "Arbol.hpp"
#include "Puzzle.hpp"
#include <vector>

using namespace std;

#ifndef CargadorXML_HPP
#define CargadorXML_HPP

class CargadorXML
{
    public:
        // Arboles
    	/*const char* SELECTOR  = "selector";
    	const char* SEL_ALEATORIO  = "selector-aleatorio";
    	const char* SECUENCIA  = "secuencia";
    	const char* SEC_ALEATORIA  = "secuencia-aleatoria";
    	const char* TAREA  = "tarea";
    	const char* ITERATOR  = "iterador";*/

        // Puzzles
    	//const int P_OPCION = 1;
    	//const int P_HANOI = 2;
    	//const int P_ARRASTRAR = 3;

        // General
        CargadorXML();

        // Arboles
        /*void CargarBehaviorTreeXml(std::string);
        void GuardarBehaviorTreeXml(std::string);*/

        // Puzzles
        void CargarPuzzlesXml();
        vector<Puzzle> GetPuzzles();

    private:
        // Arboles
        /*pugi::xml_node sacarNodo(pugi::xml_node, Nodo *, Nodo *);
        int * lista;
        Arbol *behavior_tree;*/

        // Puzzles
        vector<Puzzle> listaPuzzles;
};
#endif