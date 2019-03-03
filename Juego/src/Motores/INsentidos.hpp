#ifndef INsentidos_HPP
#define INsentidos_HPP

#include "EventoSonido.hpp"
#include "SenseEventos.hpp"

class INsentidos
{
    public:
        //virtual ~INsentidos() = default; //Activar cuando haya variables en protected
        
        virtual void generarSonido(int intensidad,double duracion,int tipo)=0;//genera un sonido

        virtual void queEscuchas()=0;//segun lo que oiga se implementa una cosa o otra

        virtual void queVes()=0;//segun lo que vea se implementa una cosa o otra
        
    /*el protected es para que tenga acceso sus descendientes o parientes*/
    protected:
        //de momento nada
};

#endif /* INsentidos_HPP */