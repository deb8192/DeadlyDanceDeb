#ifndef ESTADO_MUERTE_HPP
#define ESTADO_MUERTE_HPP

#include "../Estado.hpp"

class EstadoMuerte: public Estado {
    public:
        //singleton public
        ~EstadoMuerte();
        /*static EstadoMuerte* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new EstadoMuerte();
            }
            return _unicaInstancia;
        }*/
        //fin singleton public

        short Tipo() { return 7; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        //static EstadoMuerte* _unicaInstancia;

        void pintarBotones();
        void borrarEscenaResetearEvento(short id);
        void menuPrincipal();
        void reiniciarPartida();
        void salir();
};
#endif /* ESTADO_MUERTE_HPP */