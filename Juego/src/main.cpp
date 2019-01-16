//#include <iostream>
#include "pruebaOpengl.hpp"
#include "times.hpp"
#include "Juego.hpp"

int main()
{
	pruebaOpengl prueba;
	prueba.crearVentana();
	
	cout << "\e[42m Iniciando Juego \e[0m" << endl;
	Juego *juego = Juego::getInstance();
	times *tiempo = times::getInstance();
	
	juego->InicializarVentana();
	// se debe dar valor a las variables de interpolacion antes del bucle
	juego->setNivelThen();
	tiempo->setFrames(60,4);//definimos a cuanto queremos que vaya el programa
	while(juego->Running())//comprobamos que esta activo el dispositivo
	{
		if(tiempo->EjecutoUpdate())
		{
			if(tiempo->EjecutoIA())
			{
				juego->UpdateIA();
			}
			juego->Update();//si lo esta actualizamos la escena
		}
	}
	juego->LimpiarVentana(); //si no lo esta borramos de memoria el dispositivo
	cout << "\e[42m Cierre Juego \e[0m" << endl;
	return 0; //retornamos cero de ejecucion correcta
}
