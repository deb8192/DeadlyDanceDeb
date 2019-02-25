#ifndef CONFIGURACION_HPP
#define CONFIGURACION_HPP

#include "../Estado.hpp"

class Configuracion: public Estado {
    public:
        Configuracion();
        ~Configuracion();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        void atras();
};
#endif /* CONFIGURACION_HPP */