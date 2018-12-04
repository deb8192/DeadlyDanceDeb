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
        int getID();
        
    protected:
        int id;
        int tipo;
        std::string nombre;
        Nodo *padre;
};

class Composicion: public Nodo
{
    public:
        Composicion(int, int, Nodo*);
        void addHijo(Nodo*);
        int getID();
    private:
        std::vector<Nodo> hijos;
};

class Decorador: public Nodo
{
    public:
        Decorador(int, int, Nodo*, const char*, const char*);
        void addHijo(Nodo*);
        int getID();
    private:
        std::vector<Nodo> hijos;
        std::string fin;
        std::string alternativa;
};


class Hoja: public Nodo
{
    public:
        Hoja(int, int, Nodo*, const char*, const char*, const char*, int, const char*);
        int getID();
    private:
        std::string accion;
        std::string objetivo;
        bool pizarra;
        int tarea;
        std::string info;
};
#endif