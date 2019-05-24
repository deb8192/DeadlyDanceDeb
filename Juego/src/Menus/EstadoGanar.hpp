#ifndef EstadoGanar_HPP
#define EstadoGanar_HPP

#include "../Estado.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../puntuaciones.hpp"

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
        void siguienteNivel();
        void salir();
        unsigned int campo_user;
        unsigned int campo_pass;
        char * nombreUser;
        char * nombrePass;
        puntuaciones puntuar;//contiene la logica para subir la puntuacion
        int campoSeleccion;//que campo esta actualmente cuando es menos -1 el campo no esta seleccionado
        MotorAudioSystem* _motora;//instancia de la fachada audio
        unsigned int campo_web;
        int titulo;
};
#endif /* EstadoGanar_HPP */
