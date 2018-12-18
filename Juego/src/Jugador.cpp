#include "Jugador.hpp"
#include "Nivel.hpp"
#include <stdlib.h>
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
    //armaEquipada = NULL;
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

int Jugador::Atacar()
{
  int danyo = 0;
  if(vida > 0)
  {
    //Calcular posiciones
    atx = 5 * sin(PI * getRY() / 180.0f) + getX();
    aty = getY();
    atz = 5 * cos(PI * getRY() / 180.0f) + getZ();
    atgx = getRX();
    atgy = getRY();
    atgz = getRZ();

    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();

    //Posiciones en el mundo 3D
    atposX = (atx/2);
    atposY = (getY()/2);
    atposZ = (atz/2);

    //ATAQUE CUERPO A CUERPO
    if(tipo_arma == 1)
    {
      //Crear cuerpo de colision de ataque delante del jugador
      fisicas->crearCuerpo(atposX,atposY,atposZ,1,4,0,0,4);
      danyo = 20.0f;
    }
    //ATAQUE A DISTANCIA
    else if(tipo_arma == 2)
    {
      //Crear cuerpo de colision de ataque delante del jugador
      fisicas->crearCuerpo(atposX,atposY,atposZ,2,2,0.5,1,4);
      motora->getEvent("Bow")->start();
      danyo = 10.0f;
    }
    cout << "danyo: " << danyo << endl;
  }
  else{
      cout << "No supera las restricciones"<<endl;
  }
  return danyo;
}

void Jugador::AtacarUpdate()
{
  if(vida > 0)
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
      motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,1,1,2,3);

      //Pasar por cada uno de los enemigos del nivel y comprobar colision
      long unsigned int num = 0;
      while(nivel->getEnemies().size() > num)
      {
        //Si colisiona algun enemigo
        if(fisicas->IfCollision(fisicas->getAtack(),fisicas->getEnemies(num)))
        {
          cout << "Enemigo " << num << " danyado" << endl;
          motor->colorearEnemigo(255,255,0,0,num);
        }
        num++;
      }
    }
  }
  else{
      cout << "No supera las restricciones"<<endl;
  }
}
/*void Jugador::AtacarEspecial()
{

}*/

int Jugador::AtacarEspecial()
{
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f, por1 = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;

    //Se comprueban las restricciones (de momento solo que esta vivo y la barra de ataque especial)
    if(vida > 0 && barraAtEs == por100)
    {
        //Se calcula el danyo del ataque
        cout << "Supera las restricciones"<<endl;
        //int variacion = rand() % 21 - 10;
        if(armaEquipada != NULL)
        {
            aumentosAtaque += por1 + (float) armaEquipada->getAtaque() / por100;// + (float) variacion / 100;
            aumentosAtaque = roundf(aumentosAtaque * por10) / por10;  //FUNCION ROUND SEPARADA
        }
        aumentosAtaque += por1 + (float) armaEspecial->getAtaque()/por100;
        aumentosAtaque = roundf(aumentosAtaque * por10) / por10;

        //cout << "aumentos " << aumentosAtaque <<endl;
        int probabilidad = rand() % por100 + 1;

        //Se lanza un random y si esta dentro de la probabilidad de critico lanza un critico
        if(probabilidad <= proAtaCritico)
        {
            critico += (float) danyoCritico / por100;
            critico = roundf(critico * por10) / por10;
            cout<<"critico " << proAtaCritico << " " << critico <<endl;
        }
        //Se aplican todas las modificaciones en la variable danyo
        danyoF = ataque * critico * aumentosAtaque;
        danyo = roundf(danyoF * por10) / por10;
        cout << "daño" <<danyo<<endl;
        //barraAtEs = 0;
        return danyo;
    }
    else
    {
        cout << "No supera las restricciones"<<endl;
    }
    return danyo;
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
<<<<<<< HEAD
  vida = vid;
=======
    vida = vid;
>>>>>>> 01d553623a9ae4eec5dde1b607054590ca3d0ffe
}

void Jugador::setTipo(int tip)
{

}

void Jugador::setBarraAtEs(int bar)
{
    barraAtEs = bar;
}

void Jugador::setAtaque(int ataq)
{
    ataque = ataq;
}

void Jugador::setArma(Arma * arma)
{
    armaEquipada = arma;
}


void Jugador::setArmaEspecial(int ataque)
{
    armaEspecial = new Arma(ataque, nombreJugador);
}

void Jugador::setSuerte(int suer)
{

}

void Jugador::setDanyoCritico(int danyoC)
{
    danyoCritico = danyoC;
}

void Jugador::setProAtaCritico(int probabilidad)
{
    proAtaCritico = probabilidad;
}
void Jugador::setTimeAtEsp(float time)
{
    timeAtEsp = time;
}

int Jugador::getVida()
{
    return vida;
}

int Jugador::getTipo()
{
    return -1;
}

int Jugador::getBarraAtEs()
{
    return barraAtEs;
}

int Jugador::getAtaque()
{
    return -1;
}

Arma * Jugador::getArma()
{
    return armaEquipada;
}


Arma * Jugador::getArmaEspecial()
{
    return armaEspecial;
}

int Jugador::getSuerte()
{
    return -1;
}

int Jugador::getDanyoCritico()
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
float Jugador::getTimeAtEsp()
{
    return timeAtEsp;
}

const char *Jugador::getRutaArmaEsp()
{
    return rutaArmaEspecial;
}

void Jugador::setID(int nid)
{
    id = nid;
}

int Jugador::getID()
{
    return id;
}
