#ifndef Cofre_HPP
#define Cofre_HPP

#include "Interactuable.hpp"
#include "../Jugando/Sala.hpp"

class Cofre : public Interactuable
{
    public:
        ~Cofre();
        Cofre(bool esEne, int id,
            float x, float y, float z, unsigned short tipoObj,
            unsigned short posA, Sala* sala,unsigned short posFis);
        
        bool GetEsArana();
        Sala* GetSala();
        unsigned short GetPosArray();
        void ActivarCofre();
        void DesactivarCofre();

    private:
        bool esArana;
        Sala* _estoy;//sala en la que esta el cofre
        unsigned short posArrayArana; // Posicion en el vector de aranas
        unsigned short posFisCofre; // Posicion en el vector de cofres en fisicas
};

#endif