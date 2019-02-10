#ifndef CREDITOS_HPP
#define CREDITOS_HPP

#include "../Estado.hpp"

class Creditos: public Estado {
    public:
        //singleton public
        ~Creditos();
        /*static Creditos* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new Creditos();
            }
            return _unicaInstancia;
        }*/
        //fin singleton public

        short Tipo() { return 5; };
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();
        void Vaciar();

    private:
        //static Creditos* _unicaInstancia;

        void atras();

};
#endif /* CREDITOS_HPP */