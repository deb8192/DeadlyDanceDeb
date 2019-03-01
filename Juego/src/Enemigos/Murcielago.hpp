#ifndef Murcielago_HPP
#define Murcielago_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class Murcielago : public Enemigo
{
    public:
        ~Murcielago();
        Murcielago();
        void RunIA();
        void UpdateMurcielago(short *i);
        void SetNuevasOrdenes(short i);

    private:
        bool funciona, atacado, hecho, enZonaOscura;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;
        Zona* zonaElegida;


};

#endif
