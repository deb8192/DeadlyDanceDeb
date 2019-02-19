#ifndef RMalla_HPP
#define RMalla_HPP

#include "Recurso.hpp"

class RMalla : public Recurso
{
    public:
        
        RMalla();
        void Remove();

        //te carga los datos en la matrix
        bool CargarRecurso(const char *);
        
        //datos * CargarFrames(unsigned short,unsigned short); //le pasas datos[x]

    private:

        
        unsigned short objetos,mallas;
        //datos * para pasarlos a la entidad
        
};

#endif