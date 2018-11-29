#ifndef INsentidos_HPP
#define INsentidos_HPP

#include "eventoSonido.hpp"
#include "SenseEventos.hpp"

class INsentidos
{

public:
     virtual ~INsentidos(){};
     
     virtual void generarSonido(int intensidad,double duracion)=0;

     virtual void queEscuchas()=0;
    
/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    //de momento nada
};

#endif /* INsentidos_HPP */