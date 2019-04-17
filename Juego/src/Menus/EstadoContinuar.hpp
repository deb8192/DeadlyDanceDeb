#ifndef ESTADOCONTINUAR_HPP
#define ESTADOCONTINUAR_HPP

#include "../Estado.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Jugando/Save.hpp"

class EstadoContinuar: public Estado {
    public:
        EstadoContinuar();
        ~EstadoContinuar();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

    private:
        void atras();
        unsigned int slotSeleccionado;
        Save slots[3];//las partidas o slots cargados
        bool estadoSlot[3];//indica si existe o no la partida
        unsigned int fase;//indica en que momento del proceso para empezar la partida estamos
        MotorAudioSystem* _motora;//instancia de la fachada audio
        unsigned int id;//id del campo de error de seleccion partida
};
#endif /* ESTADOCONTINUAR_HPP */