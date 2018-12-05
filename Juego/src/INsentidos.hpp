#ifndef INsentidos_HPP
#define INsentidos_HPP

#include "eventoSonido.hpp"
#include "SenseEventos.hpp"

class INsentidos
{

public:
     virtual ~INsentidos(){}; //elimina el objeto de insentidos
     
     virtual void generarSonido(int intensidad,double duracion)=0;//genera un sonido

     virtual void queEscuchas()=0;//segun lo que oiga se implementa una cosa o otra

     virtual void queVes()=0;//segun lo que vea se implementa una cosa o otra
    
/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    //de momento nada
};

#endif /* INsentidos_HPP */