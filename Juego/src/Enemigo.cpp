#include "Enemigo.hpp"
#include "Nivel.hpp"

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
    if(animacionMuerteTiem == 0){
        return true;
    }
    return false;
}

void Enemigo::MuereEnemigo(float tiempo, int enemi){
    // los inputs los recoges siempre en un update y el valor lo utilizas también en update
    MotorGrafico* motor = MotorGrafico::getInstance();
    bool seMuere = false;

    if(seMuere || vida <= 0){
        seMuere = true;
        animacionMuerteTiem -= tiempo;
        if(animacionMuerteTiem >= 180 && animacionMuerteTiem >= 120){
            motor->colorearEnemigos(255,0,0,0,enemi);//negro
        }else if(animacionMuerteTiem <= 120 && animacionMuerteTiem >= 60){
            motor->colorearEnemigos(255,255,0,0,enemi);//rojo
        }else if(animacionMuerteTiem <=60){
            motor->colorearEnemigos(255,0,0,0,enemi);//negro
            seMuere = false;
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
