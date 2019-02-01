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
        int ContinuarSiguienteNodo(bool);
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
        
        const char* nombre;              //Nombre del nodo --LO SUYO ES DETECTAR LA CLASE--
        int cantidadNodos;               //Variable que nos indica los nodos que tiene el arbol y que ayuda a situarnos dentro del mismo
        Composicion *raiz;               //Nodo raiz del arbol
        Nodo *nodoEnEjecucionDirecta;    //Nodo actualmente en ejecucion en la IA
        bool estado;                     //Booleano que indica si el arbol se esta recorriendo o no
        bool finEjecucion;               //Si es un selector se pondra true cuando una opcion se realice; si es una secuencia se pondra true cuando todas las tareas se realicen
};
#endif