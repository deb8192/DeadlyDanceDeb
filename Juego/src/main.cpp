#include <iostream>
#include "MotorGrafico.hpp"

int main()
{
	cout << "\e[32m Iniciando Main \e[0m" << endl;
	MotorGrafico *motor = MotorGrafico::getInstance();
	if(!motor->crearVentana(1))
	{
		return 1;//no se puede crear el device	
	}//baja resolucion	
	motor->CrearCamara();//creamos la camara
	motor->crearTextoDePrueba();
	while(motor->sigueFuncionando())//comprobamos que esta activo el dispositivo
	{
		motor->updateMotor();//si lo esta actualizamos la escena
	}

	motor->limpiarDevice(); //si no lo esta borramos de memoria el dispositivo

	return 0; //retornamos cero de ejecucion correcta
}
