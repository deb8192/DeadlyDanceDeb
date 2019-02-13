#ifndef Juego_HPP
#define Juego_CPP

#include "GestorEstados.hpp"
#include "Times.hpp"
#include "Motores/MotorGrafico.hpp"

class Juego
{
    public:

        //singleton public
        ~Juego();
        static Juego* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if (_unicaInstancia == 0) {
                _unicaInstancia = new Juego();
            }
            return _unicaInstancia;
        }
        //fin singleton public

        void Iniciar();

        GestorEstados estado;
        
    private:

        //clase singleton
        Juego();
        static Juego* _unicaInstancia;
        //fin clase singleton private
        
        MotorGrafico* _motor;//instancia de la fachada
        Times* _tiempo;

        void inicializarVentana();
        void limpiarVentana();
};

#endif /* MotorGrafico_HPP */
