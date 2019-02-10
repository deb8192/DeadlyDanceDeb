//#include <iostream>
#include "pruebaOpengl.hpp"
#include "Times.hpp"
#include "Juego.hpp"

int main()
{
	//pruebaOpengl prueba;
	//prueba.crearVentana();

	cout << "\e[42m Iniciando Juego \e[0m" << endl;
	Juego* _juego = Juego::getInstance();
	Times* _tiempo = Times::GetInstance();

	_juego->InicializarVentana();
	// se debe dar valor a las variables de interpolacion antes del bucle
	//_juego->setNivelThen();
	_tiempo->SetFrames(60,15,4);//definimos a cuanto queremos que vaya el programa
	while(_juego->Running())//comprobamos que esta activo el dispositivo
	{
		if(_tiempo->EjecutoDraw())
		{
			if(_tiempo->EjecutoUpdate())
			{
				if(_tiempo->EjecutoIA())
				{
					_juego->UpdateIA();//si lo esta actualizamos la IA
				}
				_juego->Update();//si lo esta actualizamos la escena
			}
			_juego->Draw();//si lo esta dibujamos la escena
		}
	}
	_juego->LimpiarVentana(); //si no lo esta borramos de memoria el dispositivo
	cout << "\e[42m Cierre Juego \e[0m" << endl;
	return 0; //retornamos cero de ejecucion correcta
}
