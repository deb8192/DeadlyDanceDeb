#ifndef CREDITOS_HPP
#define CREDITOS_HPP

#include "../Estado.hpp"

class Creditos: public Estado {
    public:
        ~Creditos();
        short Tipo() { return 5; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        void atras();

};
#endif /* CREDITOS_HPP */