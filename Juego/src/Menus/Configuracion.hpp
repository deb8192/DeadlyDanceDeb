#ifndef CONFIGURACION_HPP
#define CONFIGURACION_HPP

#include "../Estado.hpp"

class Configuracion: public Estado {
    public:
        Configuracion();
        ~Configuracion();
        short Tipo() { return 4; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        void atras();
        
        MotorGrafico* _motor;
};
#endif /* CONFIGURACION_HPP */