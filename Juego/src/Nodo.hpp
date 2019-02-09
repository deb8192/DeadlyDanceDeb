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
        Nodo();
        Nodo(const char*, int, int, int, Nodo*);
        ~Nodo();
        int getID();
        Nodo* getPadre();
        int getNivel();
        const char* getNombre();
        int getTipo();
        
    protected:
        int id;
        int tipo;
        int nivel;
        const char* nombre;
        Nodo *padre;
};

class Composicion: public Nodo
{
    public:
        Composicion();
        Composicion(const char*, int, int, int, Nodo*, const char*, const char*, const char*, int task, const char* information, bool);
        //~Composicion();
        void addHijo(Nodo*);
        vector <Nodo*> getHijos();
        const char* GetAccion();
        const char* GetObjetivo();
        bool getAleatorio();
    private:
        std::vector<Nodo*> hijos;
        bool aleatorio;
        const char* accion;
        const char* objetivo;
        bool pizarra;
        int tarea;
        const char* info;
};

class Decorador: public Nodo
{
    public:
        Decorador();
        Decorador(const char*, int, int, int, Nodo*, const char*, const char*);
        //~Decorador();
        void addHijo(Nodo*);
        vector <Nodo*> getHijos();
        const char* GetFin();
        const char* GetAlternativa();
    private:
        std::vector<Nodo*> hijos;
        const char* fin;
        const char* alternativa;
};


class Hoja: public Nodo
{
    public:
        Hoja();
        Hoja(const char*, int, int, int, Nodo*, const char*, const char*, const char*, int, const char*);
        //~Hoja();
        const char* GetAccion();
        const char* GetObjetivo();
    private:
        const char* accion;
        const char* objetivo;
        bool pizarra;
        int tarea;
        const char* info;
};
#endif