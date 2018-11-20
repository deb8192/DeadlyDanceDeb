#include "Jugador.hpp"
#include "Enemigo.hpp"

#ifndef Nivel_HPP
#define Nivel_HPP

class Nivel 
{

    public:
        Nivel();
        
    private:
        Jugador *jugador;//objeto del jugador en el nivel
        Enemigo *enemigos[10];//objeto de los enemigos en el juego
};

#endif 
