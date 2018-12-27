#include "Enemigo.hpp"
#include "Nivel.hpp"
#include "times.hpp"

Enemigo::Enemigo()
{

}

Enemigo::~Enemigo(){

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
    //int cuantos = listaSonidos.size();
    //cout << "Esta escuchando " << cuantos << " sonidos" << endl;
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

int Enemigo::Atacar()
{
    std::cout << "Ataque normal enemigo" << std::endl;
    return 0;
}

int Enemigo::AtacarEspecial()
{
    std::cout << "Ataque especial enemigo" << std::endl;

    return -1;
}

void Enemigo::QuitarVida(int can)
{
    vida-=can;
}

bool Enemigo::estasMuerto(){
    //cout << "Muere enemigo??: " << vida << endl; 
    if(vida <= 0){
        return true;
    }
    return false;
}

bool Enemigo::finalAnimMuerte(){
    times* tiempo = times::getInstance();
    if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) >= animacionMuerteTiem && tiempoPasadoMuerte != 0){//sino se cumple no ha acabado
        return true;
    }
    return false;
}

void Enemigo::MuereEnemigo(int enemi){
    times* tiempo = times::getInstance();
    MotorGrafico* motor = MotorGrafico::getInstance();
    if(tiempoPasadoMuerte == 0){
        motor->colorearEnemigos(255,0,0,0,enemi);//negro
        tiempoPasadoMuerte = tiempo->getTiempo(1);
    }
    if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) < animacionMuerteTiem){
        if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) >= 1000.0f){
            motor->colorearEnemigos(255,255,0,0,enemi);//rojo
        }
    }
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
    vida = vid;
}

void Enemigo::setTipo(int tip)
{

}

void Enemigo::setBarraAtEs(int bar)
{

}

void Enemigo::setAtaque(int ataq)
{
    ataque = ataq;
}

void Enemigo::setSuerte(int suer)
{

}

void Enemigo::setDanyoCritico(int danyoC)
{

}

void Enemigo::setProAtaCritico(int probabilidad)
{

}

int Enemigo::getVida()
{
    return vida;
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

int Enemigo::getDanyoCritico()
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

void Enemigo::setID(int nid)
{
    id = nid;
}

int Enemigo::getID()
{
    return id;
}
