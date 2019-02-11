#ifndef ESTADO_MUERTE_HPP
#define ESTADO_MUERTE_HPP

#include "../Estado.hpp"

class EstadoMuerte: public Estado {
    public:
        ~EstadoMuerte();
        short Tipo() { return 7; };
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
        void salir();
};
#endif /* ESTADO_MUERTE_HPP */