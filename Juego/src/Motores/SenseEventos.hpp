#ifndef SenseEventos_HPP
#define SenseEventos_HPP

#include "EventoSonido.hpp"
#include <vector>//para los diferentes eventos
#include <ctime>//nos sirve para saber los tiempos de ejecucion
#include <iostream>
#include <math.h>

/*#include "MotorGrafico.hpp"
#include "MotorFisicas.hpp"*/

class SenseEventos
{
    public:
        //esta clase tiene que ser singleton porque la leen muchas entidades (solo la leen las entidades los objetos emiten)
        //clase singleton en public
        ~SenseEventos();
        static SenseEventos* getInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(_unica_instancia == 0)
                _unica_instancia = new SenseEventos();
            return _unica_instancia;  
        }
        //fin singleton public

        void update();//actualizamos los tiempos de todos los eventos, si hay alguno a cero se elimina, se llama tambien a debuggrafico
        void agregarEvento(EventoSonido* evento);//agregamos un evento de sonido
        std::vector<EventoSonido* > listarSonidos(int x, int y);
        int* listaObjetos(float x, float y, float z,float rot, float vista = 20, int modo = 1, bool perifericos = false);//devuelve los punteros y objetos que vea

    private:
        //clase singleton 
        SenseEventos();
        static SenseEventos* _unica_instancia;
        //fin clase singleton private

        std::vector<EventoSonido* > sonidos;//aqui estan todos los sonidos que se producen   
        unsigned tiempoInicio, tiempoFinal;

        /*MotorGrafico* _motor;
        MotorFisicas* _fisicas;*/
};
#endif