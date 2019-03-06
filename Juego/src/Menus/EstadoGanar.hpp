#ifndef EstadoGanar_HPP
#define EstadoGanar_HPP

#include "../Estado.hpp"

class EstadoGanar: public Estado {
    public:
        EstadoGanar();
        ~EstadoGanar();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

    private:
        void pintarBotones();
        // Para Salir y Menu principal, borra GUI y Escena
        void borrarEscenaResetearEvento(short id);
        // Para Atras y Reiniciar partida, borra solo GUI
        void borrarGUIResetearEvento(short id);
        void menuPrincipal();
        void reiniciarPartida();
        void salir();
};
#endif /* EstadoGanar_HPP */