#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#ifndef Nodo_HPP
#define Nodo_HPP

class Nodo
{
    public:
        
    protected:
        int id;
        int tipo;
        Nodo *padre;
        
};

class Composicion: public Nodo
{
    public:
        Composicion();
    private:
        std::vector<Nodo> *hijos;
};

class Decorador: public Nodo
{
    public:
        Decorador();
    private:
        std::vector<Nodo> *Shijos;
        int fin;
        int alternativa;
};


class Hoja: public Nodo
{
    public:
        Hoja();
    private:
        std::string accion;
        std::string objetivo;
        bool pizarra;
        int tarea;
        std::string info;
};
#endif