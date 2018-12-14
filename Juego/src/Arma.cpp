#include "Arma.hpp"

Arma::Arma()
{

}
Arma::Arma(int ataque, const char * ruta)
{
    motor = MotorGrafico::getInstance();
    potenciaAtaque = ataque;
    motor->CargarArmaEspecial(0,0,0,ruta,"");
}