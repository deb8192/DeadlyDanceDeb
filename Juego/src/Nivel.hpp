#include "Jugador.hpp"
#include "Enemigo.hpp"
#include "CargadorNiveles.hpp"

#ifndef Nivel_HPP
#define Nivel_HPP

class Nivel 
{

    public:
        Nivel();
        bool CargarNivel(int);
    private:
        Jugador jugador;//objeto del jugador en el nivel
        Enemigo enemigos[10];//objeto de los enemigos en el juego
        CargadorNiveles cargador;//nos ayuda a cargar los niveles
};

#endif 
