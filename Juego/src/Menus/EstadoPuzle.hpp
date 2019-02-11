#ifndef ESTADO_PUZLE_HPP
#define ESTADO_PUZLE_HPP

#include "../Estado.hpp"

class EstadoPuzle: public Estado {
    public:
        ~EstadoPuzle();
        short Tipo() { return 3; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();
        
    private:
        void atras();

};
#endif /* ESTADO_PUZLE_HPP */