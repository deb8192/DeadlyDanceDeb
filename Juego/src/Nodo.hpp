#include <iostream>

#ifndef Nodo_HPP
#define Nodo_HPP

class Nodo
{
    public:
        Nodo();
        /*Nodo(std::string, int, int, std::string, std::string, bool, int, std::string);
        std::string getNombre();
        int getId();
        int getTipo();
    private:
        std::string nombre;
        int tipo;
        int id;
        std::string accion;
        std::string objetivo;
        bool pizarra;
        int tarea;
        std::string info;*/
    
    private:
        Nodo *hijos [6];
        Nodo *padre;
};
#endif