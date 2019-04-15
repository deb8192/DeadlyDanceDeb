#ifndef MENU_HPP
#define MENU_HPP

#include "../Estado.hpp"
#include "../Motores/MotorAudio.hpp"

class Menu: public Estado {
    public:
        Menu();
        ~Menu();

        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

        void Pausar();
        void Reanudar();

    private:
        void pintarBotones();
        void borrarEscenaResetearEvento(short id);
        void jugar();
        void configuracion();
        void creditos();
        void salir();
        void calcularColor();

        short r,g,b;
        bool rm,gm,bm;

        MotorAudioSystem* _motora;//instancia de la fachada audio
};
#endif /* MENU_HPP */