#include "Jugador.hpp"

Jugador::Jugador()
{

}

Jugador::Jugador(int,int,int,int,int,int)
{
    vida = 100;//esto lo hereda de la interfaz por el protected
}

void Jugador::AtacarEspecial()
{
    cout << "Se realiza ataque especial jugador" << endl;
}