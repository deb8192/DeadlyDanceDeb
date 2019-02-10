#ifndef ESTADO_PUZLE_HPP
#define ESTADO_PUZLE_HPP

#include "../Estado.hpp"

class EstadoPuzle: public Estado {
    public:
        //singleton public
        ~EstadoPuzle();
        /*static EstadoPuzle* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new EstadoPuzle();
            }
            return _unicaInstancia;
        }*/
        //fin singleton public

        short Tipo() { return 3; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();
        
    private:
        //static EstadoPuzle* _unicaInstancia;

        void atras();

};
#endif /* ESTADO_PUZLE_HPP */