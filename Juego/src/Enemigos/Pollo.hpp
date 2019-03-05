#ifndef Pollo_HPP
#define Pollo_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class Pollo : public Enemigo
{
    public:
        ~Pollo();
        Pollo(float nX, float nY, float nZ, int maxVida);
        void RunIA();
        void UpdatePollo(short *i, int* _jug);
        void SetNuevasOrdenes(short i);

    private:
        bool funciona, atacado, hecho;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;
};

#endif