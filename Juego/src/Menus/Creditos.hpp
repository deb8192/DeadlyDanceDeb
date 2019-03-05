#ifndef CREDITOS_HPP
#define CREDITOS_HPP

#include "../Estado.hpp"

class Creditos: public Estado {
    public:
        Creditos();
        ~Creditos();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

    private:
        void atras();
};
#endif /* CREDITOS_HPP */