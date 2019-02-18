#ifndef RMalla_HPP
#define RMalla_HPP

#include "Recurso.hpp"

class RMalla : public Recurso
{
    public:
        
        RMalla();
        void Remove();
        bool CargarRecurso(const char *);
        //datos * GetMalla();

    private:

        //datos * para pasarlos a la entidad
        
};

#endif