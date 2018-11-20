#include "Jugador.hpp"
#include "MotorGrafico.hpp"
Jugador::Jugador()
{

}

Jugador::Jugador(int,int,int,int,int,int,std::string malla)
{
    
    vida = 100;//esto lo hereda de la interfaz por el protected
    MotorGrafico *motor = MotorGrafico::getInstance();
    motor->crearJugador(malla);
}

void Jugador::AtacarEspecial()
{
    cout << "Se realiza ataque especial jugador" << endl;
}