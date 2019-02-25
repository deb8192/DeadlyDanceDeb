#ifndef RTexto_HPP
#define RTexto_HPP

#include "Recurso.hpp"

class RTexto : public Recurso
{
    public:

        RTexto();
        void Remove();
        bool CargarRecurso(const char *);

    private:

};

#endif