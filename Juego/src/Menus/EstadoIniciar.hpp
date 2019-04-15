#ifndef ESTADOINICIAR_HPP
#define ESTADOINICIAR_HPP

#include "../Estado.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Jugando/Save.hpp"

class EstadoIniciar: public Estado {
    public:
        EstadoIniciar();
        ~EstadoIniciar();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

    private:
        void atras();
        unsigned int slotSeleccionado;//el slot seleccionado
        MotorAudioSystem* _motora;//instancia de la fachada audio
        unsigned int fase;//0 escoger slot, 1 escoger nombre, 2 escoger personaje
        Save slots[3];//las partidas o slots cargados
        const char * nombrePartida;//guardamos el nombre de la partida
        bool cursor;//para alternar poner o no poner cursor
        float tiempoCursor;//para saber cuando quitar o poner cursor
        unsigned int idCampoTexto;//  es el id del campo de texto que se esta controlando
        unsigned int tipo;//tipo de jugador
};
#endif /* ESTADOINICIAR_HPP */