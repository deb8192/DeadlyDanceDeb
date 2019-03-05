#ifndef ESTADO_PUZLE_HPP
#define ESTADO_PUZLE_HPP

#include "../Estado.hpp"

class EstadoPuzle: public Estado {
    public:
        EstadoPuzle();
        ~EstadoPuzle();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        
    private:
        void atras();
};
#endif /* ESTADO_PUZLE_HPP */