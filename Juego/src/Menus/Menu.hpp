#ifndef MENU_HPP
#define MENU_HPP

#include "../Estado.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Jugando/Nivel.hpp"

class Menu: public Estado {
    public:
        Menu();
        ~Menu();

        short Tipo() { return 1; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

        void Pausar();
        void Reanudar();

    private:
        void pintarBotones();
        void borrarEscenaResetearEvento(short id);
        void jugar();
        void cargarPuzzlesXML();
        void configuracion();
        void creditos();
        void salir();

        MotorGrafico* _motor;
        MotorAudioSystem* _motora;//instancia de la fachada audio
        Nivel* _nivel;
};
#endif /* MENU_HPP */