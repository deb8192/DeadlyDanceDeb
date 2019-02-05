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
        int* ContinuarSiguienteNodo(bool);
        Nodo* GetRaiz();
        Nodo* GetNodoEnEjecucionDirecta();
    private:
        
        void finBucleDecorador();

        //Variables para la comparacion de strings en el cargado y la lectura de arboles
        //Comparadores del cargado de arboles
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
        const char* RANDOM = "random";

        //Comparadores de la lectura de las acciones y objetivos de las tareas
        const char* MOVERSE = "moverse";
        const char* ATACAR = "atacar";

        const char* JUGADOR = "jugador";
        const char* ZONA_COFRES = "zona-cofres";
        
        const char* nombre;                 //Nombre del nodo --LO SUYO ES DETECTAR LA CLASE--
        int cantidadNodos;                  //Variable que nos indica los nodos que tiene el arbol y que ayuda a situarnos dentro del mismo
        Nodo *raiz;                         //Nodo raiz del arbol
        Nodo *nodoEnEjecucionDirecta;       //Nodo actualmente en ejecucion en la IA
        bool estado;                        //Booleano que indica si el arbol se esta recorriendo o no
        bool finDecorador;                  //Si es un selector se pondra true cuando una opcion se realice; si es una secuencia se pondra true cuando todas las tareas se realicen
        bool bucleDecorador;                //Variable que indica si un decorador entra en bucle o no
        vector <int> finBucle;               //Determina el valor necesario para finalizar los bucle de cada decorador
        int  *arrayTareaObjetivo;    //array de enteros que guarda la tarea y el objetivo del nodo hoja que se ejecuta en funcion continuarSiguienteNodo()
        int ID;                             //Por cada descenso, aumentara el ID y servira para elegir al siguiente hijo
        int contadorRandom;                 //Contador de las veces que se ejecuta un decorador de fin random
};
#endif