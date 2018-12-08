#include "Enemigo.hpp"

Enemigo::Enemigo()
{
    std::cout << "Con 1" << std::endl;    
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

void Enemigo::queVes()
{
    SenseEventos * eventos = SenseEventos::getInstance();
    eventos->listaObjetos(x,y);
}

Sala* Enemigo::getSala()
{
    return estoy;
}

void Enemigo::setPosiciones(int nx,int ny,int nz)
{
    x = nx;
    y = ny;
    z = nz;
}

void Enemigo::Atacar()
{
    std::cout << "Ataque normal enemigo" << std::endl;
}

void Enemigo::AtacarEspecial()
{
    std::cout << "Ataque especial enemigo" << std::endl;
}
        
void Enemigo::QuitarVida(int can)
{
            
}

void Enemigo::RecuperarVida(int can)
{

}

void Enemigo::AumentarBarraAtEs(int can)
{

} 

void Enemigo::Interactuar(int id, int id2)
{

}

void Enemigo::setVida(int vid)
{

}

void Enemigo::setTipo(int tip)
{

}

void Enemigo::setBarraAtEs(int bar)
{

}

void Enemigo::setAtaque(int ataq)
{

}

void Enemigo::setSuerte(int suer)
{

}

void Enemigo::setProAtaCritico(int probabilidad)
{

}

int Enemigo::getVida()
{
    return -1;
}

int Enemigo::getTipo()
{
    return -1;
}

int Enemigo::getBarraAtEs()
{
    return -1;
}
    
int Enemigo::getAtaque()
{
    return -1;
}

int Enemigo::getSuerte()
{
    return -1;
}

int Enemigo::getProAtaCritico()
{
    return -1;
}

int * Enemigo::getBuffos()
{
    int * valores = new int[6];
    return valores;
}