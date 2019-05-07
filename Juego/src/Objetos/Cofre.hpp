#ifndef Cofre_HPP
#define Cofre_HPP

#include "Interactuable.hpp"
#include "../Jugando/Sala.hpp"

class Cofre : public Interactuable
{
    public:
        ~Cofre();
        Cofre(bool esEne, int id,
            float x, float y, float z, unsigned int tipoObj,
            unsigned int posArana, Sala* sala, unsigned int posMotorG);

        Cofre(int id, unsigned int posMotorG, unsigned int posObs,
            float x, float y, float z, unsigned int tipoObj,
            unsigned int posArana, Sala* sala);

        void ModeloTextura();
        bool GetEsArana();
        Sala* GetSala();
        unsigned int GetPosArrayArana();
        unsigned int GetPosObs();
        void DesactivarCofre();
        void BorrarCofre();
        void Render(float updTime, float drawTime);

    private:
        bool esArana;
        Sala* _estoy;//sala en la que esta el cofre
        unsigned int posArrayArana; // Posicion en el vector de aranas
};

#endif