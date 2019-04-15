#ifndef Puerta_HPP
#define Puerta_HPP

#include "Interactuable.hpp"

class Puerta : public Interactuable
{
    public:
        ~Puerta();
        Puerta(int id, int codigo, int anc, int lar, int alt,
            float x, float y, float z, unsigned short tipoObj,
            float despX, float despZ, int accion);

        void GirarPuerta(float rotacion, bool desdePalanca);

    private:
};

#endif