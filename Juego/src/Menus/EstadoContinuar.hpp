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
        unsigned int fase;
        MotorAudioSystem* _motora;//instancia de la fachada audio
};
#endif /* ESTADOCONTINUAR_HPP */