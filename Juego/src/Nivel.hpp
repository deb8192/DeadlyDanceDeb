#include "Jugador.hpp"
#include "Enemigo.hpp"
#include "CargadorNiveles.hpp"

#ifndef Nivel_HPP
#define Nivel_HPP

class Nivel 
{

    public:

        //singleton public
        ~Nivel(void);
        static Nivel *getInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(unica_instancia == 0)
            unica_instancia = new Nivel();
            return unica_instancia;  
        }
        //fin singleton public

        bool CargarNivel(int);

    private:
        
        //clase singleton 
        Nivel();
        static Nivel* unica_instancia;
        //fin clase singleton private 

        Jugador jugador;//objeto del jugador en el nivel
        Enemigo enemigos[10];//objeto de los enemigos en el juego
        CargadorNiveles cargador;//nos ayuda a cargar los niveles
};

#endif 
