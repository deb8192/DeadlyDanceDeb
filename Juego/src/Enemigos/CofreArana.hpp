#ifndef CofreArana_HPP
#define CofreArana_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class CofreArana : public Enemigo
{
    public:
        ~CofreArana();
        CofreArana(float nX, float nY, float nZ, int maxVida,
            float anchoN, float altoN, float largoN);
        void RunIA();
        void UpdateCofreArana(short *i, int* _jug);
        void SetNuevasOrdenes(short i);
        float GetAncho();
        float GetAlto();
        float GetLargo();

    private:
        bool funciona, atacado, hecho;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;
        float ancho, alto, largo;
};

#endif
