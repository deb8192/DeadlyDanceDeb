#ifndef JUGANDO_HPP
#define JUGANDO_HPP

#include "../Estado.hpp"
#include "Nivel.hpp"

class Jugando: public Estado {
    public:
        Jugando();
        ~Jugando();

        //clase singleton en public
        static Jugando* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(!_unica_instancia)
                _unica_instancia = new Jugando();
            return _unica_instancia;  
        }
        //fin singleton public

        void Iniciar();
        void Render();
        void Update();
        void UpdateIA();
        void ManejarEventos();
        void Vaciar();
        void Pausar();
        void Reanudar();
        void Reiniciar();

    private:
        //clase singleton 
        static Jugando* _unica_instancia;
        //fin clase singleton private

        bool reiniciando;

        MotorAudioSystem* _motora;
        SenseEventos* _sense;
        MotorGrafico* _motor;
        MotorFisicas* _fisicas;
        Nivel* _nivel;
};
#endif /* JUGANDO_HPP */