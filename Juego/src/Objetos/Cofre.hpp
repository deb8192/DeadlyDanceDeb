#ifndef Cofre_HPP
#define Cofre_HPP

#include "Interactuable.hpp"
#include "../Jugando/Sala.hpp"

class Cofre : public Interactuable
{
    public:
        ~Cofre();
        Cofre();
        Cofre(bool esEne, int id,
            float x, float y, float z, unsigned int tipoObj,
            unsigned int posA, Sala* sala);

        Cofre(int id, unsigned int pos,
            float x, float y, float z, unsigned int tipoObj,
            unsigned int posA, Sala* sala);

        void ModeloTextura();
        bool GetEsArana();
        Sala* GetSala();
        unsigned short GetPosArray();
        void DesactivarCofre(unsigned int pos);
        void BorrarCofre(unsigned int pos);
        void Render(float updTime, float drawTime);

    private:
        bool esArana;
        Sala* _estoy;//sala en la que esta el cofre
        unsigned short posArrayArana; // Posicion en el vector de aranas
};

#endif