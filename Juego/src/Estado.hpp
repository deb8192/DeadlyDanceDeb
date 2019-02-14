#ifndef ESTADO_HPP
#define ESTADO_HPP

#include "Motores/MotorGrafico.hpp"
using namespace idsEventos;

//aqui definimos la clase interfaz de los estados
class Estado {
    public:
        //funciones que tiene la interfaz como virtual (porque no existen pero deberian)
        virtual short Tipo() = 0;
        virtual void Iniciar() = 0;
        virtual void Render() = 0;
        virtual void Update() = 0;
        virtual void UpdateIA() { };//solo va en EstadoJugando

        virtual void ManejarEventos() = 0;
        virtual void Vaciar() = 0;
        virtual void Pausar() { }
        virtual void Reanudar() { }

    private:
        
};
#endif /* ESTADO_HPP */
