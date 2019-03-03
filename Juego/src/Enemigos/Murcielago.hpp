#ifndef Murcielago_HPP
#define Murcielago_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.
#include "../Jugando/Jugando.hpp"

class Murcielago : public Enemigo
{
    public:
        ~Murcielago();
        Murcielago(float nX, float nY, float nZ, int maxVida);
        void RunIA();
        void UpdateMurcielago(short *i);
        void SetNuevasOrdenes(short i);

    private:
        bool funciona, atacado, hecho, enZonaOscura;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;
        Zona* zonaElegida;

        Jugando* _nivel;
};

#endif
