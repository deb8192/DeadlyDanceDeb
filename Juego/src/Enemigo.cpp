#include "Enemigo.hpp"
#include "Nivel.hpp"
#include "times.hpp"

#define PI 3.14159265358979323846
#define PIRADIAN 180.0f

Enemigo::Enemigo()
{

}

float Enemigo::getX()
{
    return x;
}

float Enemigo::getY()
{
    return y;
}

float Enemigo::getZ()
{
    return z;
}

float Enemigo::getRX()
{
    return rx;
}

float Enemigo::getRY()
{
    return ry;
}

float Enemigo::getRZ()
{
    return rz;
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
    //SenseEventos * eventos = SenseEventos::getInstance();
    //esto es un ejemplo

    /*
    int * loqueve = eventos->listaObjetos(x,y,z,rotation,20); //le pedimos al motor de sentidos que nos diga lo que vemos y nos devuelve una lista

    if(loqueve != nullptr)
    {
        if(loqueve[0] == 1)
        {
            std::cout << "ve al jugador" << std::endl;
        }
    }
    delete loqueve;
    */

    //esto hay que editarlo para cada llamada segun el arbol de comportamientos puesto que a veces interesara ver ciertas cosas, si se le pasa 1 despues del 20 vera solo al jugador si esta, si es 2 se vera los objetos, si es 3 vera los enemigos(para socorrerlos)

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
    int danyo = 0;
    if(vida > 0 && atacktime == 0)
    {
      MotorFisicas* fisicas = MotorFisicas::getInstance();
      //MotorAudioSystem* motora = MotorAudioSystem::getInstance();

      //Calcular posiciones
      int distance= 2;
      atx = distance * sin(PI * getRY() / 180.0f) + getX();
      aty = getY();
      atz = distance * cos(PI * getRY() / 180.0f) + getZ();
      atgx = getRX();
      atgy = getRY();
      atgz = getRZ();

      fisicas->crearCuerpo(0,atx/2,aty/2,atz/2,2,1,1,1,7);

      //Colision
      if(fisicas->IfCollision(fisicas->getEnemiesAtack(),fisicas->getJugador()))
      {
        cout << "Jugador Atacado" << endl;
        danyo = 5.0f;
        cout << "danyo del enemigo -> " << danyo << endl;
      }
    }
    else
    {
        //cout << "No supera las restricciones"<<endl;
    }
    return danyo;
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

void Enemigo::setRotation(float rot)
{
    rotation = rot;
}

void Enemigo::setAtackTime(float t)
{
  atacktime = t;
}

float Enemigo::getAtackTime()
{
  return atacktime;
}
