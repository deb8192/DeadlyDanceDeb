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
        // Para Salir y Menu principal, borra GUI y Escena
        void borrarEscenaResetearEvento(short id);
        // Para Atras y Reiniciar partida, borra solo GUI
        void borrarGUIResetearEvento(short id);
        void menuPrincipal();
        void reiniciarPartida();
        void atras();
        void salir();
};
#endif /* PAUSA_HPP */