#ifndef Palanca_HPP
#define Palanca_HPP

#include "Interactuable.hpp"

class Palanca : public Interactuable
{
    public:
        ~Palanca();
        Palanca(int id, int codigo, int anc, int lar, int alt,
            float x, float y, float z, unsigned short tipoObj,
            float despX, float despZ, int accion);
        void Render(float updTime, float drawTime);
        
    private:
};

#endif