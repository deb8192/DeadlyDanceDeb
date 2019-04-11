#ifndef ESTADOINICIAR_HPP
#define ESTADOINICIAR_HPP

#include "../Estado.hpp"

class EstadoIniciar: public Estado {
    public:
        EstadoIniciar();
        ~EstadoIniciar();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

    private:
        void atras();
        unsigned int slotSeleccionado;
};
#endif /* ESTADOINICIAR_HPP */