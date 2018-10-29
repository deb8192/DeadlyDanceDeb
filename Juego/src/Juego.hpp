#include "MotorGrafico.hpp"

#ifndef Juego_HPP
#define Juego_CPP

    class Juego
    {
        public:

            //singleton public
            ~Juego(void);
            static Juego *getInstance() //esto se utiliza para crear el objeto una sola vez
            {
                if(unica_instancia == 0)
                unica_instancia = new Juego();
                return unica_instancia;  
            }
            //fin singleton public

            bool Running();//te devuelve true si esta en funcionamiento la ventana del juego, te devuelve false si se ha cerrado la ventana
            void InicializarVentana();//te inicializa la ventana en la que se va a mostrar el juego
            void Update(); //actualiza las ia, renderizados, control de teclas
            void LimpiarVentana();//borra de la memoria la ventana del juego.

        private:

            //clase singleton 
            Juego();
            static Juego* unica_instancia;
            //fin clase singleton private

            MotorGrafico *motor;//instancia de la fachada
    };

#endif /* MotorGrafico_HPP */