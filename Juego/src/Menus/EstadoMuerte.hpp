#ifndef ESTADO_MUERTE_HPP
#define ESTADO_MUERTE_HPP

#include "../Estado.hpp"
#include "../Motores/MotorAudio.hpp"

class EstadoMuerte: public Estado {
    public:
        EstadoMuerte();
        ~EstadoMuerte();

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

        MotorAudioSystem* _motora;
        int titulo;
};
#endif /* ESTADO_MUERTE_HPP */
