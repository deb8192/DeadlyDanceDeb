#ifndef Enemigo_HPP
#define Enemigo_HPP

#include "INnpc.hpp"
#include "INdrawable.hpp"
#include "INsentidos.hpp"
#include "Sala.hpp"
#include <vector>

class Enemigo : public INnpc , public INdrawable, public INsentidos //multiple herencia a esto se le llama derivacion multiple
{

    public:
        Enemigo();
        void definirSala(Sala * sala);
        void generarSonido(int intensidad, double duracion);
        void queEscuchas();
    private:
        Sala * estoy;//sala en la que esta el enemigo
};

#endif 