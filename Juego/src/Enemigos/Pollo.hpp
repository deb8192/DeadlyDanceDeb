#ifndef Pollo_HPP
#define Pollo_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class Pollo : public Enemigo
{
    public:
        ~Pollo();
        Pollo();
        void RunIA();
        void UpdatePollo(int i);
        void SetNuevasOrdenes(short int i);

    private:
        bool funciona, atacado, hecho;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;

};

#endif
