#ifndef CINEMATICA_HPP
#define CINEMATICA_HPP

#include "../Estado.hpp"

class Cinematica: public Estado {
    public:
        //singleton public
        ~Cinematica();
        /*static Cinematica* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new Cinematica();
            }
            return _unicaInstancia;
        }*/
        //fin singleton public

        short Tipo() { return 1; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        //static Cinematica* _unicaInstancia;
};
#endif /* CINEMATICA_HPP */