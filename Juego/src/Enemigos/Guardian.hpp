#ifndef Guardian_HPP
#define Guardian_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.
#include "stack"

class Guardian : public Enemigo
{
    public:
        ~Guardian();
        Guardian(float nX, float nY, float nZ, int maxVida, int disfraz);
        void RunIA();
        void UpdateGuardian(short *i, int* _jug, std::vector<Zona*> &_getZonas);
        void SetNuevasOrdenes(short i);
        void SetNuevosObjetivos(short i);

    private:
        bool funciona, hecho, escondido, atacado, forzadoCambio;
        short int* _ordenes;
        short int direccion;
        std::stack<VectorEspacial> puertasAtravesadas;
        Zona* zonaElegida;
};

#endif
