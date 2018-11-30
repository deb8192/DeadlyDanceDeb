#include "Enemigo.hpp"

Enemigo::Enemigo()
{
    
}

void Enemigo::definirSala(Sala * sala)
{
    estoy = sala;
}

void Enemigo::generarSonido(int intensidad, double duracion)
{
    eventoSonido * sonid = new eventoSonido(intensidad,duracion,x,y,z,1,1);
    SenseEventos * eventos = SenseEventos::getInstance();
    eventos->agregarEvento(sonid);
}

void Enemigo::queEscuchas()
{
    SenseEventos * eventos = SenseEventos::getInstance();
    std::vector<eventoSonido *> listaSonidos =  eventos->listarSonidos(x,y);//le pasamos nuestra x e y
    int cuantos = listaSonidos.size();
    cout << "Esta escuchando " << cuantos << " sonidos" << endl;
}
