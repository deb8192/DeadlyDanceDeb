#ifndef CINEMATICA_HPP
#define CINEMATICA_HPP

#include "../Estado.hpp"
#include "../Times.hpp"

class Cinematica: public Estado {
    public:
        Cinematica();
        ~Cinematica();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void CambiarMenu();

    private:
        Times* _tiempo;
        float tiempoTotal;//esto indica el tiempo de las cinematicas total en segundos
        float marcaTiempo;//llamaremos a getiempo cuando se inicialice la ventana luego simplemente comprobamos que el tiempo sea mayor que el total para cambiar a menu
        float tiempoUltimoFrame;
        bool cambiar;
};
#endif /* CINEMATICA_HPP */