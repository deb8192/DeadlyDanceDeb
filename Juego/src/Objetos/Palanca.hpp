#ifndef Palanca_HPP
#define Palanca_HPP

#include "Interactuable.hpp"

class Palanca : public Interactuable
{
    public:
        ~Palanca();
        Palanca(int codigo, const char* nombre, int anc, int lar, int alt,
            int posicion, float x, float y, float z, unsigned short tipoObj);
        
        void CrearFisica();
        void BorrarFisica();
        
    private:
};

#endif