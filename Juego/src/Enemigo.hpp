#ifndef Enemigo_HPP
#define Enemigo_HPP

#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "Sala.hpp"

class Enemigo : public INnpc , public INdrawable //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();
        void definirSala(Sala * sala);
    private:
        Sala * estoy;//sala en la que esta el enemigo
};

#endif 