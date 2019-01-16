#include "Jugador.hpp"
#include "Nivel.hpp"
#include <stdlib.h>
#include "MotorAudio.hpp"
#include "math.h"
#include "times.hpp"

#define PI 3.14159265358979323846
#define PIRADIAN 180.0f
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define NOMBREHEAVY "Heavy"
#define NOMBREBAILAORA "Bailaora"

Jugador::Jugador()
{
    animacion = 0;

    //tiempos de animacion
    tiempoAtaque=2000.0f;//tiempo en milisegundos
    tiempoPasadoAtaque=0;
    tiempoAtaEsp=2000.0f;//tiempo en milisegundos
    tiempoPasadoAtaEsp=0;
    tiempoCogerObjeto=1000.0f;//tiempo en milisegundos
    tiempoPasadoCogerObjeto=0;
    tiempoEnMorir=2000.0f;//tiempo en milisegundos
    tiempoPasadoEnMorir=0;

}

Jugador::~Jugador()
{
    armaEquipada=nullptr;
    armaEspecial=nullptr;
}

Jugador::Jugador(int,int,int,int,int,int,std::string malla)
{

    vida = 100;//esto lo hereda de la interfaz por el protected
    MotorGrafico *motor = MotorGrafico::getInstance();
    motor->crearJugador(malla);

    x = 1;
    z = 20;
    animacion = 0;
    //armaEquipada = NULL;

    //tiempos de animacion
    tiempoAtaque=2000.0f;//tiempo en milisegundos
    tiempoPasadoAtaque=0;
    tiempoAtaEsp=2000.0f;//tiempo en milisegundos
    tiempoPasadoAtaEsp=0;
    tiempoCogerObjeto=2000.0f;//tiempo en milisegundos
    tiempoPasadoCogerObjeto=0;
    tiempoEnMorir=2000.0f;//tiempo en milisegundos
    tiempoPasadoEnMorir=0;
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

float Jugador::getNewX()
{
    return newX;
}

float Jugador::getNewY()
{
    return newY;
}

float Jugador::getNewZ()
{
    return newZ;
}

float Jugador::getLastX()
{
    return lastX;
}

float Jugador::getLastY()
{
    return lastY;
}

float Jugador::getLastZ()
{
    return lastZ;
}

float Jugador::getFisX()
{
    return fisX;
}

float Jugador::getFisY()
{
    return fisY;
}

float Jugador::getFisZ()
{
    return fisZ;
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

    if(w || s || a || d)
    {
        setAnimacion(1);
    }
    else
    {
        setAnimacion(0);//no se mueve
    }

    // Comprobar teclas para mover el personaje y la camara
    if(w)
    {
        //ax y az son las componentes del vector director (x,z), para calcular el angulo posteriormente.
        az += 50.0; //cuando mas alto mejor es el efecto de giro
    }
    if(s)
    {
        az += -50.0;
    }
    if(a)
    {
        ax += -50.0;

    }
    if(d)
    {
        ax += 50.0;
    }

    //Esto es para que az y ax no aumente de valores excesivamente
    //valores de muchas cifras hace que tarde mas en hacer el giro y que le cueste
    if(az < -10000 || az > 10000)
    {
        az = 10;
    }
    if(ax < -10000 || ax > 10000)
    {
        ax = 0;
    }

    //Para giro: obtienes el maximo comun divisor y lo divides entre x, z
    //asi tambien evitas que ambas variables aumenten excesivamente de valor
        float div = (float)__gcd((int)abs(ax),(int)abs(az));

        if(div != 1.0 && div != 0.0)
        {
            ax /= div;
            az /= div;
        }

    //cout << "ax: " << ax << ", az: " << az << endl;

    //esto es para que gire hacia atras ya que al valor que devuelve atan hay que darle la vuelta 180
    az < 0 ?
        deg = PIRADIAN + (RADTODEG * atan(ax/az)) :
        deg =  RADTODEG * atan(ax/az) ;

    float componente;
    if(w || s || a || d)
    {
        componente = 1.0;
    }
    else
    {
        componente = 0.0;
    }
    px += componente*sin(deg*DEGTORAD)/**dt*/;
    pz += componente*cos(deg*DEGTORAD)/**dt*/;


    //cout << "deg: " << deg << ", px:" << px << ", pz:" << pz << endl;
    //ahora actualizas movimiento y rotacion
    //has obtenido la arcotangente que te da el angulo de giro en grados
    x = px;
    z = pz;
    //setNewPosiciones(px, y, pz);
    ry = deg;
}

/*************** moverseEscenario *****************
 * Funcion con la que el enemigo se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Jugador::moverseEscenario(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    x = lastX * (1 - pt) + newX * pt;
    z = lastZ * (1 - pt) + newZ * pt;
}

void Jugador::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
}

void Jugador::setPosiciones(float nx,float ny,float nz)
{
    x = nx;
    y = ny;
    z = nz;
}


void Jugador::setLastPosiciones(float nx,float ny,float nz)
{
    lastX = nx;
    lastY = ny;
    lastZ = nz;
}

void Jugador::setNewPosiciones(float nx,float ny,float nz)
{
    this->setLastPosiciones(newX, newY, newZ);
    newX = nx;
    newY = ny;
    newZ = nz;
}

void Jugador::initPosicionesFisicas(float nx,float ny,float nz)
{
    fisX = nx;
    fisY = ny;
    fisZ = nz;
}

void Jugador::setPosicionesFisicas(float nx,float ny,float nz)
{
    fisX += nx;
    fisY += ny;
    fisZ += nz;
}

bool Jugador::estasMuerto(){
    //cout << "Muere jugador??: " << vida << endl;
    if(vida <= 0){
        setAnimacion(5);
        return true;
    }
    return false;
}

bool Jugador::finalAnimMuerte(){

    times* tiempo = times::getInstance();
    if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) >= animacionMuerteTiem && tiempoPasadoMuerte != 0){//sino se cumple no ha acabado
        return true;
    }
    return false;
}

void Jugador::MuereJugador(){
    times* tiempo = times::getInstance();
    MotorGrafico* motor = MotorGrafico::getInstance();

    if(tiempoPasadoMuerte == 0){
        motor->colorearJugador(255,0,0,0);//negro
        tiempoPasadoMuerte = tiempo->getTiempo(1);
        motor->botonesMuerteJugador();//PINTAR BOTON 'REINICIAR JUEGO' Y 'IR A MENU'
    }
    if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) < animacionMuerteTiem){
        if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) >= 1000.0f){
            motor->colorearJugador(255,255,0,0);//rojo
        }
    }
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
    if(this->getArma() == nullptr)distance= 3;
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
    if(this->getArma() == nullptr){
      setAnimacion(2);
      fisicas->crearCuerpo(0,atposX,atposY,atposZ,2,2,1,1,4);
      danyo = 50.0f;
      motora->getEvent("SinArma")->setVolume(0.8f);
      motora->getEvent("SinArma")->start();
    }
    //ATAQUE CUERPO A CUERPO
    else if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)
    {
      //Crear cuerpo de colision de ataque delante del jugador
      fisicas->crearCuerpo(0,atposX,atposY,atposZ,1,4,0,0,4);
      danyo = 70.0f;
      motora->getEvent("GolpeGuitarra")->setVolume(0.8f);
      motora->getEvent("GolpeGuitarra")->start();
    }
    //ATAQUE A DISTANCIA
    else if(strcmp(this->getArma()->getNombre(),"arpa") == 0)
    {
      //Crear cuerpo de colision de ataque delante del jugador
      fisicas->crearCuerpo(0,atposX,atposY,atposZ,2,2,0.5,1,4);
      danyo = 55.0f;
      motora->getEvent("Arpa")->setVolume(0.8f);
      motora->getEvent("Arpa")->start();
    }
    atacados_normal.clear(); //Reiniciar vector con enemigos atacados
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
    if(this->getArma() == nullptr){
      fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      motor->clearDebug2();
      motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,2,1,1,2);
    }
    else if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)
    {
      fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      motor->clearDebug2();
      motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,3,1,3,1);
    }
    else if(strcmp(this->getArma()->getNombre(),"arpa") == 0)
    {
      atz += (0.02 * cos(PI * atgy / PIRADIAN));
      atx += (0.02 * sin(PI * atgy / PIRADIAN));
      atposZ += (0.02 * cos(PI * atgy / PIRADIAN));
      atposX += (0.02 * sin(PI * atgy / PIRADIAN));


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
                break;
              }
              j++;
            }
          }
          //Si no se ha encontrado es que no se le a atacado
          if (encontrado == false)
          {
            float variacion = rand() % 7 - 3;
            danyo += (int) variacion;
            nivel->getEnemigos().at(atacados.at(i))->QuitarVida(danyo);
            cout<<"Enemigo: "<< nivel->getEnemigos().at(atacados.at(i))->getID() << endl;
            cout<<"Daño "<<danyo<<endl;
            danyo -= (int) variacion;
            cout<<"variacion "<<variacion<<endl;
            cout<<"Vida enemigo "<<nivel->getEnemigos().at(atacados.at(i))->getID()<<" "<<nivel->getEnemigos().at(atacados.at(i))->getVida()<<endl;
            motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
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
/*************** AtacarEspecial *****************
 *  Funcion que inicia la ejecucion del ataque
 *  especial del jugador si la barra de ataque
 *  especial esta completa y se pulsa el boton Q /
 *  click derecho del raton.
 *      Entradas:
 *      Salidas: int danyo;
 */
int Jugador::AtacarEspecial()
{
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f, por1 = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;

    cout << vida << " " << barraAtEs << " " << por100 << endl;
    //Se comprueban las restricciones (de momento solo que esta vivo y la barra de ataque especial)
    if(vida > 0 && barraAtEs == por100)
    {
        cout << "Supera las restricciones, ATAQUE ESPECIAL"<<endl;
        //Calcular posiciones si se inicia el ataque especial
        setAnimacion(3);
        if(atackEspTime <= 0)
        {
            animacion = 3;
            atespx = 6.5 * sin(PI * getRY() / PIRADIAN) + getX();
            atespy = getY();
            atespz = 6.5 * cos(PI * getRY() / PIRADIAN) + getZ();
            atgx = getRX();
            atgy = getRY();
            atgz = getRZ();
            incrAtDisCirc = 0.0;

            MotorFisicas* fisicas = MotorFisicas::getInstance();
            MotorAudioSystem* motora = MotorAudioSystem::getInstance();

            //Posiciones en el mundo 3D
            atespposX = (atespx/2);
            atespposY = (getY()/2);
            atespposZ = (atespz/2);

            //ATAQUE ESPECIAL DEL HEAVY
            if(strcmp(armaEspecial->getNombre(), NOMBREHEAVY) == 0)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                fisicas->crearCuerpo(0,atespposX,atespposY,atespposZ,2,8,1,8,5);
                motora->getEvent("Arpa")->setVolume(0.8f);
                motora->getEvent("Arpa")->start();
            }
            //ATAQUE ESPECIAL DE LA BAILAORA
            else if(strcmp(armaEspecial->getNombre(), NOMBREBAILAORA) == 0)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                fisicas->crearCuerpo(0,atespposX,atespposY,atespposZ,2,8,8,8,5);
                motora->getEvent("Arpa")->start();
            }
        }

        //Se calcula el danyo del ataque
        aumentosAtaque += por1;
        if(armaEquipada != NULL)
        {
            aumentosAtaque += (float) armaEquipada->getAtaque() / por100;// + (float) variacion / 100;
            //aumentosAtaque = roundf(aumentosAtaque * por10) / por10;  //FUNCION ROUND SEPARADA
        }
        aumentosAtaque *= 2;
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
        cout << "daño: " <<danyo<<endl;
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
/*************** AtacarEspecialUpdate *****************
 *  Funcion que actualiza la posicion y
 *  la colision del ataque especial
 *      Entradas: int danyo
 *      Salidas:
 */
void Jugador::AtacarEspecialUpdate(int *danyo)
{
    MotorGrafico * motor = MotorGrafico::getInstance();
    MotorFisicas * fisicas = MotorFisicas::getInstance();
    Nivel* nivel = Nivel::getInstance();

    //Si el ataque especial es el del Heavy, es cuerpo a cuerpo
    if(strcmp(armaEspecial->getNombre(), NOMBREHEAVY) == 0)
    {

        //Calculo de la posicion del arma delante  int getAnimacion();del jugador
        atespx = 6.5 * sin(PI * this->getRY() / PIRADIAN) + this->getX();
        atespz = 6.5 * cos(PI * this->getRY() / PIRADIAN) + this->getZ();
        atespposX = atespx/2;
        atespposZ = atespz/2;
        atgy = this->getY();


        motor->mostrarArmaEspecial(
            this->getX(),
            this->getY(),
            this->getZ(),
            this->getRX(),
            this->getRY(),
            this->getRZ());

        motor->clearDebug2();   //Pruebas debug

        motor->dibujarObjetoTemporal(
            atespx,
            this->getY(),
            atespz,
            this->getRX(),
            this->getRY(),
            this->getRZ(),
            8,
            1,
            8,
            2);
    }

    //Si el ataque especial es el de la Bailaora, es circular a distancia
    else if(strcmp(armaEspecial->getNombre(), NOMBREBAILAORA) == 0)
    {
        //Formula de ataque circular aumentando la distancia
        incrAtDisCirc += 0.02;
        atespz = this->getZ();
        atespz += (incrAtDisCirc * cos(PI * atgy / PIRADIAN));
        atespx = this->getX();
        atespx += (incrAtDisCirc * sin(PI * atgy / PIRADIAN));
        atespposZ = atespz/2;
        atespposX = atespx/2;

        //Aumento de la rotacion hacia la izquierda.
        atgy += 0.75;

        if(atgy >= 360.0)
        {
            atgy -= 360.0;
        }
        else if(atgy < 0.0)
        {
            atgy += 360;
        }

        motor->mostrarArmaEspecial(
            atespx,
            atespy,
            atespz,
            atgx,
            atgy,
            atgz);

        motor->clearDebug2(); //Pruebas debug

        motor->dibujarObjetoTemporal(
            atespx,
            atespy,
            atespz,
            atgx,
            atgy,
            atgz,
            8,
            1,
            8,
            3);
    }
    //lista de enteros que senyalan a los enemigos atacados
    vector <unsigned int> atacados = fisicas->updateArmaEspecial(atespposX,atgy,atespposZ);

    //Si hay colisiones se danya a los enemigos colisionados anyadiendole una variacion al danyo
    //y se colorean los enemigos danyados (actualmente todos al ser instancias de una malla) de color verde
    if(!atacados.empty() && *danyo > 0)
    {
        cout<<"Funciona"<<endl;
        for(unsigned int i = 0; i < atacados.size(); i++)
        {
            float variacion = rand() % 7 - 3;
            *danyo += (int) variacion;
            nivel->getEnemigos().at(atacados.at(i))->QuitarVida(*danyo);
            cout<<"Daño "<<*danyo<<endl;
            *danyo -= (int) variacion;
            cout<<"variacion "<<variacion<<endl;
            cout<<"Vida enemigo "<<nivel->getEnemigos().at(atacados.at(i))->getID()<<" "<<nivel->getEnemigos().at(atacados.at(i))->getVida()<<endl;
            motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
        }
    }
}

void Jugador::QuitarVida(int can)
{
  vida-=can;
  this->AumentarBarraAtEs(can);
}

void Jugador::RecuperarVida(int can)
{

}

void Jugador::AumentarBarraAtEs(int can)
{
    barraAtEs += can;
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
    if(bar >= 0 && bar <= 100)
    {
        barraAtEs = bar;
    }
    else
    {
        if(bar < 0)
         barraAtEs = 0;
        if(bar > 100)
         barraAtEs = 100;
    }
}

void Jugador::setAtaque(int ataq)
{
    ataque = ataq;
}

void Jugador::setArma(Arma * arma)
{
    armaEquipada = arma;
    if(this->getArma() != nullptr)
    {
        if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            InterfazJugador * interfaz = InterfazJugador::getInstance();
            interfaz->setArma(2);
        }

        if(strcmp(this->getArma()->getNombre(),"arpa") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            InterfazJugador * interfaz = InterfazJugador::getInstance();
            interfaz->setArma(3);
        }

        if(strcmp(this->getArma()->getNombre(),"llave") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            InterfazJugador * interfaz = InterfazJugador::getInstance();
            interfaz->setArma(1);
        }

        if(strcmp(this->getArma()->getNombre(),"dinero") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            InterfazJugador * interfaz = InterfazJugador::getInstance();
            dinero = dinero+1;
            interfaz->setArma(0);
        }
    }
    else
    {
        InterfazJugador * interfaz = InterfazJugador::getInstance();
        interfaz->setArma(0);
    }
}


void Jugador::setArmaEspecial(int ataque)
{
    armaEspecial = new Arma(ataque, nombreJugador,3,3,3,rutaArmaEspecial,"");
}

void Jugador::setNombre(const char * nombre)
{
    nombreJugador = nombre;
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
    atackEspTime = time;
}

void Jugador::setLastTimeAtEsp(float time)
{
    lastAtackEspTime = time;
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
    if(barraAtEs >= 0 && barraAtEs <= 100)
    {
        return barraAtEs;
    }
    else
    {
        if(barraAtEs < 0)
            return 0;
        if(barraAtEs > 100)
            return 100;
    }

    return 1;
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

const char* Jugador::getNombre()
{
    return nombreJugador;
}

int Jugador::getSuerte()
{
    return -1;
}

int Jugador::getDanyoCritico()
{
    return danyoCritico;
}

int Jugador::getProAtaCritico()
{
    return proAtaCritico;
}

int * Jugador::getBuffos()
{
    int * valores = new int[6];
    return valores;
}
float Jugador::getTimeAtEsp()
{
    return atackEspTime;
}

float Jugador::getLastTimeAtEsp()
{
    return lastAtackEspTime;
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

void Jugador::updateInterfaz()
{
    InterfazJugador * interfaz = InterfazJugador::getInstance();
    interfaz->setVida(vida);
    interfaz->setAtaqueEspecial(getBarraAtEs());
    interfaz->setDinero(dinero);
}

int Jugador::getAnimacion()
{
    return animacion;
}

void Jugador::setAnimacion(int est)
{
    times * tiempo = times::getInstance();

    if(est != animacion)
    {
        //es una nueva animacion
        if(terminaAnimacion())
        {
            animacion = est; //cambiamos la animacion
            switch(animacion)
            {
                case 2:
                    tiempoPasadoAtaque = tiempo->getTiempo(1);
                break;
                case 3:
                    tiempoPasadoAtaEsp = tiempo->getTiempo(1);
                break;
                case 4:
                    tiempoPasadoCogerObjeto = tiempo->getTiempo(1);
                break;
            }
        }
    }
    else
    {
        //es la misma comprobamos si ha terminado si lo a echo nos ponemos en modo reposo o corriendo
        if(terminaAnimacion() && animacion != 0 && animacion != 1)
        {
            animacion = 0;//pasamos a modo reposo si no esta corriendo o en modo reposo
        }
    }
}

bool Jugador::terminaAnimacion()
{
        times * tiempo = times::getInstance();

        switch(animacion)//comprobamos que la animacion haya terminado
        {
            case 0://andar
                return true;
            case 1://quieto
                return true;
            case 2://ataque
                if(tiempo->calcularTiempoPasado(tiempoPasadoAtaque) >= tiempoAtaque || tiempoPasadoAtaque == 0)
                {
                    tiempoPasadoAtaque = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 3://ataque especial
                if(tiempo->calcularTiempoPasado(tiempoPasadoAtaEsp) >=  tiempoAtaEsp || tiempoPasadoAtaEsp == 0)
                {
                    tiempoPasadoAtaEsp = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 4://coger objeto
                if(tiempo->calcularTiempoPasado(tiempoPasadoCogerObjeto) >= tiempoCogerObjeto || tiempoPasadoCogerObjeto == 0)
                {
                    tiempoPasadoCogerObjeto = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 5://muerto
                return false;
        }
    return true;
}
