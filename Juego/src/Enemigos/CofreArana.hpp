#ifndef CofreArana_HPP
#define CofreArana_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class CofreArana : public Enemigo
{
    public:
        ~CofreArana();
        CofreArana(float nX, float nY, float nZ, int maxVida,
            float anchoN, float altoN, float largoN, Sala* salaC);
        void RunIA();
        void UpdateCofreArana(short *i, int* _jug, bool ayuda);
        void SetNuevasOrdenes(short i);
        float GetAncho();
        float GetAlto();
        float GetLargo();
        int GetIdCofre();
        unsigned int GetPosMotorCofre();
        unsigned int GetPosObsCofre();
        unsigned int GetPosArana();
        bool GetActivada();
        void SetIdCofre(int idC);
        void SetPosMotorCofre(unsigned int pos);
        void SetPosObsCofre(unsigned int pos);
        void SetPosArana(unsigned int pos);
        void SetActivada(bool estado);

    private:
        bool funciona, atacado, hecho;
        short int* _ordenes;
        short int maxRotacion;
        short int direccion;
        float ancho, alto, largo;

        int idCofre;
        Sala* sala;
        unsigned int posMotorCofre;
        unsigned int posObsCofre;
        unsigned int posArana;
        bool activada;
};

#endif