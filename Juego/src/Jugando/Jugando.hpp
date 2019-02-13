#ifndef JUGANDO_HPP
#define JUGANDO_HPP

#include "../Estado.hpp"

class Jugando: public Estado {
    public:
        //singleton public
        ~Jugando();
        static Jugando* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new Jugando();
            }
            return _unicaInstancia;
        }
        //fin singleton public

        short Tipo() { return 2; };
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
    static Jugando* _unicaInstancia;

    bool reiniciando;
    
};
#endif /* JUGANDO_HPP */