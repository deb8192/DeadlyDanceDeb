#ifndef pollo_HPP
#define pollo_HPP

#include "Enemigo.hpp"
#include <iostream> //la utilizamos para mostrar el log en la consola.

class pollo : public Enemigo
{
    public:
        ~pollo();
        pollo();
        void runIA();
        void updatePollo();

    private:
        bool funciona;
        int* ordenes;

};

#endif
