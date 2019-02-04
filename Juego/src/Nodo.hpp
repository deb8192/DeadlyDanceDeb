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
        std::string GetAccion();
        std::string GetObjetivo();
        bool getAleatorio();
    private:
        std::vector<Nodo*> hijos;
        bool aleatorio;
        std::string accion;
        std::string objetivo;
        bool pizarra;
        int tarea;
        std::string info;
};

class Decorador: public Nodo
{
    public:
        Decorador();
        Decorador(const char*, int, int, int, Nodo*, const char*, const char*);
        //~Decorador();
        void addHijo(Nodo*);
        vector <Nodo*> getHijos();
    private:
        std::vector<Nodo*> hijos;
        std::string fin;
        std::string alternativa;
};


class Hoja: public Nodo
{
    public:
        Hoja();
        Hoja(const char*, int, int, int, Nodo*, const char*, const char*, const char*, int, const char*);
        //~Hoja();
        std::string GetAccion();
        std::string GetObjetivo();
    private:
        std::string accion;
        std::string objetivo;
        bool pizarra;
        int tarea;
        std::string info;
};
#endif