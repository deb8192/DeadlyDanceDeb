#ifndef Puerta_HPP
#define Puerta_HPP

#include "Interactuable.hpp"

class Puerta : public Interactuable
{
    public:
        ~Puerta();
        Puerta(int codigo, const char* nombre, int anc, int lar, int alt,
            int posicion, float x, float y, float z, unsigned short tipoObj);
        
        void CrearFisica();
        void BorrarFisica();

    private:
};

#endif