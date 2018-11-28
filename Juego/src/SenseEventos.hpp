#ifndef SenseEventos_HPP
#define SenseEventos_HPP

#include "eventoSonido.hpp"
#include <vector>//para los diferentes eventos

class SenseEventos
{
    public:
        //esta clase tiene que ser singleton porque la leen muchas entidades (solo la leen las entidades los objetos emiten)

        //clase singleton en public
        ~SenseEventos(void);
        static SenseEventos *getInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(unica_instancia == 0)
            unica_instancia = new SenseEventos();
            return unica_instancia;  
        }
        //fin singleton public

    private:
    
        //clase singleton 
        SenseEventos();
        static SenseEventos* unica_instancia;
        //fin clase singleton private

        std::vector<eventoSonido *> sonidos;//aqui estan todos los sonidos que se producen   
};

#endif