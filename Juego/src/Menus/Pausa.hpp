#ifndef PAUSA_HPP
#define PAUSA_HPP

#include "../Estado.hpp"

class Pausa: public Estado {
    public:
        Pausa();
        ~Pausa();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        void pintarBotones();
        void borrarEscenaResetearEvento(short id);
        void menuPrincipal();
        void reiniciarPartida();
        void atras();
        void salir();

        MotorGrafico* _motor;
};
#endif /* PAUSA_HPP */