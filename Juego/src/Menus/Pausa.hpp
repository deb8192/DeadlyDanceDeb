#ifndef PAUSA_HPP
#define PAUSA_HPP

#include "../Estado.hpp"

class Pausa: public Estado {
    public:

        ~Pausa();
        short Tipo() { return 6; };
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
};
#endif /* PAUSA_HPP */