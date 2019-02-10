#ifndef CONFIGURACION_HPP
#define CONFIGURACION_HPP

#include "../Estado.hpp"

class Configuracion: public Estado {
    public:
        //singleton public
        ~Configuracion();
        /*static Configuracion* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new Configuracion();
            }
            return _unicaInstancia;
        }*/
        //fin singleton public

        short Tipo() { return 4; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        //static Configuracion* _unicaInstancia;

        void atras();

};
#endif /* CONFIGURACION_HPP */