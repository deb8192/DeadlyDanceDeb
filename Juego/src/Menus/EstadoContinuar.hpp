#ifndef ESTADOCONTINUAR_HPP
#define ESTADOCONTINUAR_HPP

#include "../Estado.hpp"

class EstadoContinuar: public Estado {
    public:
        EstadoContinuar();
        ~EstadoContinuar();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

    private:
        void atras();
        unsigned int slotSeleccionado;
};
#endif /* ESTADOCONTINUAR_HPP */