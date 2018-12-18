#ifndef SenseEventos_HPP
#define SenseEventos_HPP

#include "eventoSonido.hpp"
#include <vector>//para los diferentes eventos
#include <ctime>//nos sirve para saber los tiempos de ejecucion
#include <iostream>
#include <math.h>

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

        void update();//actualizamos los tiempos de todos los eventos, si hay alguno a cero se elimina, se llama tambien a debuggrafico
        
        void agregarEvento(eventoSonido * evento);//agregamos un evento de sonido

        std::vector<eventoSonido *> listarSonidos(int x, int y);

        void listaObjetos(int x, int y);//devuelve los punteros y objetos que vea

    private:
    
        //clase singleton 
        SenseEventos();
        static SenseEventos* unica_instancia;
        //fin clase singleton private

        std::vector<eventoSonido *> sonidos;//aqui estan todos los sonidos que se producen   
        unsigned tiempoInicio, tiempoFinal;
};

#endif