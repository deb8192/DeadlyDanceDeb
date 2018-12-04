#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#ifndef Nodo_HPP
#define Nodo_HPP

using namespace std;

class Nodo
{
    public:
        virtual int getID();
        virtual const char*  getNombre();
        
    protected:
        int id;
        int tipo;
        const char* nombre;
        Nodo *padre;
};

class Composicion: public Nodo
{
    public:
        Composicion(const char*, int, int, Nodo*);
        void addHijo(Nodo*);
        int getID();
        const char* getNombre();
    private:
        std::vector<Nodo> hijos;
};

class Decorador: public Nodo
{
    public:
        Decorador(const char*, int, int, Nodo*, const char*, const char*);
        void addHijo(Nodo*);
        int getID();
        const char* getNombre();
    private:
        std::vector<Nodo> hijos;
        std::string fin;
        std::string alternativa;
};


class Hoja: public Nodo
{
    public:
        Hoja(const char*, int, int, Nodo*, const char*, const char*, const char*, int, const char*);
        int getID();
        const char* getNombre();
    private:
        std::string accion;
        std::string objetivo;
        bool pizarra;
        int tarea;
        std::string info;
};
#endif