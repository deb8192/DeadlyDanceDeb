#ifndef CINEMATICA_HPP
#define CINEMATICA_HPP

#include "../Estado.hpp"

class Cinematica: public Estado {
    public:
        Cinematica();
        ~Cinematica();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
};
#endif /* CINEMATICA_HPP */