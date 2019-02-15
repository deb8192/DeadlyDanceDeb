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
        void Vaciar();

    private:
        void atras();
        MotorGrafico* _motor;

};
#endif /* CREDITOS_HPP */