#ifndef Cofre_HPP
#define Cofre_HPP

#include "Interactuable.hpp"

class Cofre : public Interactuable
{
    public:
        ~Cofre();
        Cofre(bool esEne, int codigo, const char* nombre, int anc, int lar, int alt,
            int posicion, float x, float y, float z, unsigned short tipoObj);
        

    private:
        bool esArana;
};

#endif