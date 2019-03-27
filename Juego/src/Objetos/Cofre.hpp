#ifndef Cofre_HPP
#define Cofre_HPP

#include "Interactuable.hpp"
#include "../Jugando/Sala.hpp"

class Cofre : public Interactuable
{
    public:
        ~Cofre();
        Cofre(bool esEne, int codigo, const char* nombre, 
            int anc, int lar, int alt, int posicion,
            float x, float y, float z, unsigned short tipoObj,
            unsigned short posA, Sala* sala);
        
        bool GetEsArana();
        Sala* GetSala();
        unsigned short GetPosArray();
        void CrearFisica();
        void BorrarFisica();

    private:
        bool esArana;
        Sala* _estoy;//sala en la que esta el cofre
        unsigned short posArrayArana; // Vector de aranas
        vector<int> posArrayFisicas;
};

#endif