#include <iostream>
#include "Juego.hpp"

int main()
{
	cout << "\e[42m Iniciando Juego \e[0m" << endl;
	Juego *juego = Juego::getInstance();
	juego->InicializarVentana();

	while(juego->Running())//comprobamos que esta activo el dispositivo
	{
		juego->Update();//si lo esta actualizamos la escena
	}
	juego->LimpiarVentana(); //si no lo esta borramos de memoria el dispositivo
	cout << "\e[42m Cierre Juego \e[0m" << endl;
	return 0; //retornamos cero de ejecucion correcta
}
