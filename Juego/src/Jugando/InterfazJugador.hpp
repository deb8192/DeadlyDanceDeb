#ifndef InterfazJugador_HPP
#define InterfazJugador_HPP

#include "../Motores/MotorGrafico.hpp"

class InterfazJugador
{
    public:
        //esta clase tiene que ser singleton porque la leen muchas entidades (solo la leen las entidades los objetos emiten)

        //clase singleton en public
        InterfazJugador();
        ~InterfazJugador();
        static InterfazJugador* getInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(!_unica_instancia)
                _unica_instancia = new InterfazJugador();
            return _unica_instancia;  
        }
        //fin singleton public
        void activar();//activa la interfaz
        void desactivar();//desactiva la interfaz
        bool getEstado();//devuelve si debe ser visible o no la interfaz
        void setVida(int);//0 a 100, si te sales o bajas se queda en los limites
        void setAtaqueEspecial(int);//0 a 100
        void setDinero(int);//0 a 9999, si llegas a esa cantidad eres rico.
        void setArma(int);//0 al (maximo 100) numero de armas que hay

    private:
        //clase singleton 
        static InterfazJugador* _unica_instancia;
        //fin clase singleton private

        MotorGrafico* _motor;
        Constantes constantes;
        bool estado;//true o false
};

#endif