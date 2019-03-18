#include <iostream>
#include "Juego.hpp"

int main()
{
	Juego::GetInstance();
	Juego::GetInstance()->Iniciar();
	cout << "\e[42m Cierre Juego \e[0m" << endl;
	return 0; //retornamos cero de ejecucion correcta
}
