#ifndef Pared_HPP
#define Pared_HPP

#include "Interactuable.hpp"

class Pared : public Interactuable
{
    public:
        ~Pared();
        Pared(int id, int codigo, int anc, int lar, int alt,
            float x, float y, float z, unsigned short tipoObj,
            float despX, float despZ, int accion);

        void Borrar(unsigned short pos);
        
    private:
};

#endif