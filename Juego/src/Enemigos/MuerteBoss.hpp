#ifndef MuerteBoss_HPP
#define MuerteBoss_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class MuerteBoss : public Enemigo
{
    public:
        ~MuerteBoss();
        MuerteBoss(float nX, float nY, float nZ, int maxVida);
        void RunIA();
        void UpdateMuerteBoss(short *i, int* _jug);
        void SetNuevasOrdenes(short i);

    private:
        bool funciona, atacado, hecho;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;
};

#endif