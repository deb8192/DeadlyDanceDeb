#ifndef CofreArana_HPP
#define CofreArana_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class CofreArana : public Enemigo
{
    public:
        ~CofreArana();
        CofreArana(float nX, float nY, float nZ, int maxVida);
        void RunIA();
        void UpdateCofreArana(short *i, int* _jug, bool ayuda);
        void SetNuevasOrdenes(short i);

    private:
        bool funciona, atacado, hecho;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;
};

#endif
