#include "Enemigo.hpp"
#include "Nivel.hpp"

#define PI 3.14159265358979323846

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

      fisicas->crearCuerpo(atx/2,aty/2,atz/2,2,1,1,1,6);

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

void Enemigo::setAtackTime(float t)
{
  atacktime = t;
}

float Enemigo::getAtackTime()
{
  return atacktime;
}
