#ifndef TravornioBoss_HPP
#define TravornioBoss_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class TravornioBoss : public Enemigo
{
    public:
        ~TravornioBoss();
        TravornioBoss(float nX, float nY, float nZ, int maxVida);
        void RunIA();
        void UpdateTravornioBoss(short *i, int* _jug, bool ayuda);
        void SetNuevasOrdenes(short newOrden);
        void SetAtaqueEspecial();

    private:
        bool funciona, atacado, ataqueEspecial, hecho, seAcerca;
        short int* _ordenes;
        short int direccion;
        int minDistanciaJugador, maxDistanciaJugador;
};

#endif