#ifndef Cofre_HPP
#define Cofre_HPP

#include "Interactuable.hpp"
#include "../Jugando/Sala.hpp"

class Cofre : public Interactuable
{
    public:
        ~Cofre();
        Cofre(bool esEne, int codigo, const char* nombre, int anc, int lar, int alt,
            int posicion, float x, float y, float z, unsigned short tipoObj, Sala* sala);
        
        bool GetEsArana();
        Sala* GetSala();

    private:
        bool esArana;
        Sala* _estoy;//sala en la que esta el cofre
};

#endif