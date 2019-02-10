#ifndef PAUSA_HPP
#define PAUSA_HPP

#include "../Estado.hpp"

class Pausa: public Estado {
    public:
        //singleton public
        ~Pausa();
        /*static Pausa* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new Pausa();
            }
            return _unicaInstancia;
        }*/
        //fin singleton public

        short Tipo() { return 6; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        //static Pausa* _unicaInstancia;

        void pintarBotones();
        void borrarEscenaResetearEvento(short id);
        void menuPrincipal();
        void reiniciarPartida();
        void atras();
        void salir();
};
#endif /* PAUSA_HPP */