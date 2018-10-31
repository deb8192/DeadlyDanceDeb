#include "Juego.hpp"

//para clases singleton deben tener un indicador de que se ha creado el unico objeto
Juego* Juego::unica_instancia = 0;
//fin indicador singleton

Juego::Juego()
{
    motor = MotorGrafico::getInstance();
}

bool Juego::Running()
{
    return motor->sigueFuncionando();
}

void Juego::LimpiarVentana()
{
    motor->limpiarDevice();
}

void Juego::InicializarVentana()
{
    motor->crearVentana(3);//crea ventana
    motor->CrearCamara();//creamos la camara
	motor->crearTextoDePrueba();//crea un texto
}

void Juego::Update()
{
    motor->updateMotor();
}