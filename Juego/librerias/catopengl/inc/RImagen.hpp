#ifndef RImagen_HPP
#define RImagen_HPP

#include "Recurso.hpp"

class RImagen : public Recurso 
{
    
    public: 

        RImagen();
        void Remove();//destruye el recurso de memoria
        bool CargarRecurso(char const *);

    private:

        unsigned int height;
        unsigned int width;

};

#endif