#include "Jugador.hpp"
#include "Nivel.hpp"
#include <stdlib.h>
#include "MotorAudio.hpp"
#include "math.h"

#define PI 3.14159265358979323846
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define NOMBREHEABY "Heavy"
#define NOMBREBAILAORA "Bailaora"

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
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();

    //Calcular posiciones que no se modifican
    int distance = 5;
    if(tipo_arma == 0)distance= 3;
    atx = distance * sin(PI * getRY() / 180.0f) + getX();
    aty = getY();
    atz = distance * cos(PI * getRY() / 180.0f) + getZ();
    atgx = getRX();
    atgy = getRY();
    atgz = getRZ();

    //Posiciones en el mundo 3D
    atposX = (atx/2);
    atposY = (getY()/2);
    atposZ = (atz/2);

    //ATAQUE SIN ARMA
    if(tipo_arma == 0){
      fisicas->crearCuerpo(atposX,atposY,atposZ,2,2,1,1,4);
      danyo = 5.0f;
    }
    //ATAQUE CUERPO A CUERPO
    else if(tipo_arma == 1)
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
      danyo = 10.0f;
    }
    motora->getEvent("Bow")->setVolume(0.8f);
    motora->getEvent("Bow")->start();
    atacados_normal.clear(); //Riniciar vector con enemigos atacados
  }
  else{
      cout << "No supera las restricciones"<<endl;
  }
  return danyo;
}

void Jugador::AtacarUpdate(int danyo)
{
  if(vida > 0)
  {
    Nivel* nivel = Nivel::getInstance();
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorGrafico * motor = MotorGrafico::getInstance();
    if(tipo_arma == 0){
      fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      motor->clearDebug2();
      motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,2,1,1,2);
    }
    else if(tipo_arma == 1)
    {
      fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      motor->clearDebug2();
      motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,3,1,3,1);
    }
    else if(tipo_arma == 2)
    {
      atz += (0.02 * cos(PI * atgy / 180.0f));
      atx += (0.02 * sin(PI * atgy / 180.0f));
      atposZ += (0.02 * cos(PI * atgy / 180.0f));
      atposX += (0.02 * sin(PI * atgy / 180.0f));

      fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      motor->clearDebug2();
      motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,1,1,2,3);
    }

    //Enteros con los enemigos colisionados (atacados)
    vector <unsigned int> atacados = fisicas->updateArma(atposX,atposY,atposZ);

    if(!atacados.empty())
    {
        //Pasar por cada uno de los atacados
        for(unsigned int i = 0; i < atacados.size(); i++)
        {
          //Buscar si esta en el vector guardado
          bool encontrado = false;
          long unsigned int j = 0;
          if(!atacados_normal.empty())
          {
            while(j < atacados_normal.size())
            {
              if(atacados.at(i) == atacados_normal.at(j))
              {
                encontrado = true; //Ya se le ha atacado antes
              }
              j++;
            }
          }
          //Si no se ha encontrado es que no se le a atacado
          if (encontrado == false)
          {
            float variacion = rand() % 7 - 3;
            danyo += (int) variacion;
            nivel->getEnemigos().at(i)->QuitarVida(danyo);
            cout<<"Daño "<<danyo<<endl;
            danyo -= (int) variacion;
            cout<<"variacion "<<variacion<<endl;
            cout<<"Vida enemigo "<<nivel->getEnemigos().at(i)->getID()<<" "<<nivel->getEnemigos().at(i)->getVida()<<endl;
            motor->colorearEnemigos(255, 0, 255, 55, atacados.at(i));
            //guardar el atacado para no repetir
            atacados_normal.push_back(atacados.at(i));
          }
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
        cout << "Supera las restricciones, ATAQUE ESPECIAL"<<endl;

        //Calcular posiciones
        atespx = 6.5 * sin(PI * getRY() / 180.0f) + getX();
        atespy = getY();
        atespz = 6.5 * cos(PI * getRY() / 180.0f) + getZ();
        atgx = getRX();
        atgy = getRY();
        atgz = getRZ();

        MotorFisicas* fisicas = MotorFisicas::getInstance();
        MotorAudioSystem* motora = MotorAudioSystem::getInstance();

        //Posiciones en el mundo 3D
        atespposX = (atespx/2);
        atespposY = (getY()/2);
        atespposZ = (atespz/2);

        //ATAQUE ESPECIAL DEL HEAVY
        if(strcmp(armaEspecial->getNombre(), NOMBREHEABY) == 0)
        {
            //Crear cuerpo de colision de ataque delante del jugador
            fisicas->crearCuerpo(atespposX,atespposY,atespposZ,2,8,1,8,5);
            motora->getEvent("Bow")->setVolume(0.8f);
            motora->getEvent("Bow")->start();
        }
        //ATAQUE ESPECIAL DE LA BAILAORA
        else if(strcmp(armaEspecial->getNombre(), NOMBREBAILAORA) == 0)
        {
            //Crear cuerpo de colision de ataque delante del jugador
            /*fisicas->crearCuerpo(atposX,atposY,atposZ,2,2,0.5,1,4);
            motora->getEvent("Bow")->start();*/
        }

        //Se calcula el danyo del ataque
        if(armaEquipada != NULL)
        {
            aumentosAtaque += por1 + (float) armaEquipada->getAtaque() / por100;// + (float) variacion / 100;
            aumentosAtaque = roundf(aumentosAtaque * por10) / por10;  //FUNCION ROUND SEPARADA
        }
        aumentosAtaque += por1 + (float) armaEspecial->getAtaque()/por100;
        aumentosAtaque = roundf(aumentosAtaque * por10) / por10;

        //Se lanza un random y si esta dentro de la probabilidad de critico lanza un critico
        int probabilidad = rand() % por100 + 1;
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
        barraAtEs = 0;
        return danyo;
    }
    else
    {
        cout << "No supera las restricciones"<<endl;
        barraAtEs = por100;
    }
    return danyo;
}

void Jugador::AtacarEspecialUpdate(int *danyo)
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    MotorFisicas * fisicas = MotorFisicas::getInstance();
    Nivel* nivel = Nivel::getInstance();

    atespx = 6.5 * sin(PI * this->getRY() / 180.0f) + this->getX();
    atespz = 6.5 * cos(PI * this->getRY() / 180.0f) + this->getZ();
    atespposX = atespx/2;
    atespposZ = atespz/2;

    //lista de enteros que senyalan a los enemigos atacados
    vector <unsigned int> atacados = fisicas->updateArmaEspecial(atespposX,this->getY(),atespposZ);

    //Si hay colisiones se danya a los enemigos colisionados anyadiendole una variacion al danyo
    //y se colorean los enemigos danyados (actualmente todos al ser instancias de una malla) de color verde
    if(!atacados.empty() && *danyo > 0)
    {
        cout<<"Funciona"<<endl;
        for(unsigned int i = 0; i < atacados.size(); i++)
        {
            float variacion = rand() % 7 - 3;
            *danyo += (int) variacion;
            nivel->getEnemigos().at(i)->QuitarVida(*danyo);
            cout<<"Daño "<<*danyo<<endl;
            *danyo -= (int) variacion;
            cout<<"variacion "<<variacion<<endl;
            cout<<"Vida enemigo "<<nivel->getEnemigos().at(i)->getID()<<" "<<nivel->getEnemigos().at(i)->getVida()<<endl;
            motor->colorearEnemigos(255, 0, 255, 55, atacados.at(i));
        }
    }
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
    vida = vid;
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
