#ifndef CREDITOS_HPP
#define CREDITOS_HPP

#include "../Estado.hpp"

class Creditos: public Estado {
    public:
        Creditos();
        ~Creditos();
        short Tipo() { return 5; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        void atras();
        MotorGrafico* _motor;

};
#endif /* CREDITOS_HPP */