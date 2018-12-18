#include "Jugador.hpp"
#include "Nivel.hpp"
#include "MotorFisicas.hpp"
#include "MotorGrafico.hpp"
#include "MotorAudio.hpp"
#include "math.h"

#define PI 3.14159265358979323846
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Jugador::Jugador()
{

}

Jugador::Jugador(int,int,int,int,int,int)
{
    vida = 100;//esto lo hereda de la interfaz por el protected
}

float Jugador::getX()
{
    return x;
}

float Jugador::getY()
{
    return y;
}

float Jugador::getZ()
{
    return z;
}

float Jugador::getRX()
{
    return rx;
}

float Jugador::getRY()
{
    return ry;
}

float Jugador::getRZ()
{
    return rz;
}


void Jugador::movimiento(float dt,bool a, bool s, bool d, bool w)
{
    float px = x,
          pz = z;

    // Comprobar teclas para mover el personaje y la camara
    if(w)
    {
        //globales usadas para calcular giro, como vector director (x,z)
        az += 50.0; //cuando mas alto mejor es el efecto de giro
        az < -1000 ? az = 0 : false;
        //dir es un vector director usado para incrementar el movimiento
        pz += 1.0*dt;
    }
    if(s)
    {
        az += -50.0;
        az > 1000 ? az = 0 : false;
        pz += -1.0*dt;
    }
    if(a)
    {
        ax += -50.0;
        ax > 1000 ? ax = 0 : false;
        px += -1.0*dt;

    }
    if(d)
    {
        ax += 50.0;
        ax < -1000 ? ax = 0 : false;
        px += 1.0*dt;
    }

    //Para giro: obtienes el maximo comun divisor y lo divides entre x, z
    //asi evitas que ambas variables aumenten excesivamente de valor
        float div = (float)__gcd((int)abs(ax),(int)abs(az));

        if(div != 1.0)
        {
            ax /= div;
            az /= div;
        }

    //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
    az < 0 ?
        deg = 180 + (RADTODEG * atan(ax/az)) :
        deg =  RADTODEG * atan(ax/az) ;

    //ahora actualizas movimiento y rotacion
    //has obtenido la arcotangente que te da el angulo de giro en grados
    x = px;
    z = pz;
    ry = deg;
}

void Jugador::setPosiciones(int nx,int ny,int nz)
{
    x = nx;
    y = ny;
    z = nz;
}

void Jugador::Atacar()
{
    cout << "ATAQUE NORMAL DEL JUGADOR" << endl;
    Nivel* nivel = Nivel::getInstance();

    //Calcular posiciones
    atx = sin(PI * getRY() / 180.0f) + getX();
    aty = getY();
    atz = cos(PI * getRY() / 180.0f) + getZ();
    atgx = getRX();
    atgy = getRY();
    atgz = getRZ();

    MotorGrafico * motor = MotorGrafico::getInstance();
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();
    rp3d::CollisionBody * cuerpo;

    //Posiciones en el mundo 3D
    atposX = (atx/2);
    atposY = (getY()/2);
    atposZ = (atz/2);

    //ATAQUE CUERPO A CUERPO
    if(tipo_arma == 1)
    {
      //DEBUG DEL ATAQUE Crear cuerpo
      motor->dibujarObjetoTemporal(atx,getY(),atz,getRX(),getRY(),getRZ(),3,3,3,1);

      //Crear cuerpo de colision de ataque delante del jugador
      fisicas->crearCuerpo(atposX,atposY,atposZ,1,4,0,0,4);
      cuerpo = fisicas->getAtack();
    }
    //ATAQUE A DISTANCIA
    else if(tipo_arma == 2)
    {
      //DEBUG DEL ATAQUE Crear cuerpo
      motor->dibujarObjetoTemporal(atx,getY(),atz,getRX(),getRY(),getRZ(),1,1,2,2);

      //Crear cuerpo de colision de ataque delante del jugador
      fisicas->crearCuerpo(atposX,atposY,atposZ,2,2,0.5,1,4);
      cuerpo = fisicas->getAtack();

      //Sonido
      //motora->getEvent("Bow")->setVolume(0.5f);
      motora->getEvent("Bow")->start();
    }

    if(cuerpo != nullptr)
    {
      //Pasar por cada uno de los enemigos del nivel y comprobar colision
      long unsigned int num = 0;
      while(nivel->getEnemies().size() > num)
      {
        //Si colisiona algun enemigo
        if(fisicas->getWorld()->testOverlap(cuerpo,fisicas->getEnemies(num)))
        {
          cout << "Enemigo " << num << " danyado" << endl;
          motor->colorearEnemigo(255,255,0,0,num);
        }
        num++;
      }

      //Destruir cuerpo colision
      //fisicas->getWorld()->destroyCollisionBody(cuerpo);
    }
}

void Jugador::AtacarUpdate()
{
  Nivel* nivel = Nivel::getInstance();
  MotorFisicas* fisicas = MotorFisicas::getInstance();
  MotorGrafico * motor = MotorGrafico::getInstance();
  if(tipo_arma == 2)
  {
    atz += (0.02 * cos(PI * atgy / 180.0f));
    atx += (0.02 * sin(PI * atgy / 180.0f));
    atposZ += (0.02 * cos(PI * atgy / 180.0f));
    atposX += (0.02 * sin(PI * atgy / 180.0f));

    fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
    motor->clearDebug2();
    motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,1,1,2,2);
  }

  //Pasar por cada uno de los enemigos del nivel y comprobar colision
  long unsigned int num = 0;
  while(nivel->getEnemies().size() > num)
  {
    //Si colisiona algun enemigo
    if(fisicas->getWorld()->testOverlap(fisicas->getAtack(),fisicas->getEnemies(num)))
    {
      cout << "Enemigo " << num << " danyado" << endl;
      motor->colorearEnemigo(255,255,0,0,num);
    }
    num++;
  }
}

void Jugador::AtacarEspecial()
{

}

void Jugador::QuitarVida(int can)
{

}

void Jugador::RecuperarVida(int can)
{

}

void Jugador::AumentarBarraAtEs(int can)
{

}

void Jugador::Interactuar(int id, int id2)
{

}

void Jugador::setVida(int vid)
{

}

void Jugador::setTipo(int tip)
{

}

void Jugador::setBarraAtEs(int bar)
{

}

void Jugador::setAtaque(int ataq)
{

}

void Jugador::setSuerte(int suer)
{

}

void Jugador::setProAtaCritico(int probabilidad)
{

}

int Jugador::getVida()
{
    return -1;
}

int Jugador::getTipo()
{
    return -1;
}

int Jugador::getBarraAtEs()
{
    return -1;
}

int Jugador::getAtaque()
{
    return -1;
}

int Jugador::getSuerte()
{
    return -1;
}

int Jugador::getProAtaCritico()
{
    return -1;
}

int * Jugador::getBuffos()
{
    int * valores = new int[6];
    return valores;
}

void Jugador::setID(int nid)
{
    id = nid;
}

int Jugador::getID()
{
    return id;
}
