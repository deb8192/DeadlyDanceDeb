#include "Jugador.hpp"
#include "../Jugando/Nivel.hpp"
#include <stdlib.h>
#include "../MotorAudio.hpp"
#include "../Times.hpp"

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
    //Poner variables con los valores iniciales que tenían
    ax = 1.0f;
    az = 20.0f;
    deg = 0.0f;
    _armaEquipada=nullptr;
    _armaEspecial=nullptr;
    //const char* _rutaArmaEspecial = "assets/models/Arma.obj";
    //const char* _nombreJugador = "Heavy";
    danyo_arma = 10.0f;
    atx=0.0;
    atespx=0.0;
    aty=0.0;
    atespy=0.0;
    atz=0.0;
    atespz=0.0;
    atgx=0.0;
    atgy=0.0;
    atgz=0.0;
    incrAtDisCirc=0.0;
    atposX=0.0;
    atespposX=0.0;
    atposY=0.0;
    atespposY=0.0;
    atposZ=0.0;
    atespposZ=0.0;
    tipo_arma = 2;
    //vector <unsigned int> atacados_normal;
    dinero = 0;
}

Jugador::Jugador(int,int,int,int,int,int,std::string malla)
{

    vida = 100;//esto lo hereda de la interfaz por el protected
    MotorGrafico* _motor = MotorGrafico::GetInstance();
    _motor->crearJugador(malla);

    posActual.x = 1;
    posActual.z = 20;
    animacion = 0;
    //_armaEquipada = NULL;

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

void Jugador::movimiento(bool noMueve,bool a, bool s, bool d, bool w)
{
    float px = posFutura.x,
          pz = posFutura.z;

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
        az = 50; //cuando mas alto mejor es el efecto de giro
    }
    if(s)
    {
        az = -50;
    }
    if(a)
    {
        ax = -50;

    }
    if(d)
    {
        ax = 50;
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
    if((w || s || a || d) && !noMueve)
    {
        componente = 1.5;
    }
    else
    {
        componente = 0.0;
    }
    px += componente*sin(deg*DEGTORAD);
    pz += componente*cos(deg*DEGTORAD);


    //cout << "deg: " << deg << ", px:" << px << ", pz:" << pz << endl;
    //ahora actualizas movimiento y rotacion
    //has obtenido la arcotangente que te da el angulo de giro en grados
    /*x = px;
    z = pz;*/
    setNewPosiciones(px, posActual.y, pz);
    setNewRotacion(rotActual.x, deg, rotActual.z);
}

/*************** moverseEntidad *****************
 * Funcion con la que el jugador se desplazaran
 * por el escenario mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Jugador::moverseEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    posActual.x = posPasada.x * (1 - pt) + posFutura.x * pt;
    posActual.z = posPasada.z * (1 - pt) + posFutura.z * pt;
}

/*************** rotarEntidad *****************
 * Funcion con la que el jugador rotara
 * sobre si mismo mediante una interpolacion desde
 * el punto de origen al punto de destino
 */
void Jugador::RotarEntidad(float updTime)
{
    //pt es el porcentaje de tiempo pasado desde la posicion
    //de update antigua hasta la nueva
    float pt = moveTime / updTime;

    if(pt > 1.0f)
    {
        pt = 1.0f;
    }

    rotActual.x = rotPasada.x * (1 - pt) + rotFutura.x * pt;
    rotActual.y = rotPasada.y * (1 - pt) + rotFutura.y * pt;
    rotActual.z = rotPasada.z * (1 - pt) + rotFutura.z * pt;
}

void Jugador::UpdateTimeMove(float updTime)
{
    moveTime += updTime;
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

    Times* _tiempo = Times::GetInstance();
    if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) >= animacionMuerteTiem && tiempoPasadoMuerte != 0){//sino se cumple no ha acabado
        return true;
    }
    return false;
}

void Jugador::MuereJugador(){
    Times* _tiempo = Times::GetInstance();
    MotorGrafico* _motor = MotorGrafico::GetInstance();

    if(tiempoPasadoMuerte == 0){
        _motor->colorearJugador(255,0,0,0);//negro
        tiempoPasadoMuerte = _tiempo->GetTiempo(1);
        _motor->botonesMuerteJugador();//PINTAR BOTON 'REINICIAR JUEGO' Y 'IR A MENU'
    }
    if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) < animacionMuerteTiem){
        if(_tiempo->CalcularTiempoPasado(tiempoPasadoMuerte) >= 1000.0f){
            _motor->colorearJugador(255,255,0,0);//rojo
        }
    }
}

int Jugador::Atacar(int i)
{
  int danyo = 0;
  if(vida > 0)
  {
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    MotorAudioSystem* _motora = MotorAudioSystem::getInstance();

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
      _fisicas->crearCuerpo(0,atposX,atposY,atposZ,2,2,2,1,4);
      danyo = 50.0f;
      _motora->getEvent("SinArma")->setVolume(0.8f);
      _motora->getEvent("SinArma")->start();
    }
    //ATAQUE CUERPO A CUERPO
    else if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)
    {
      //Crear cuerpo de colision de ataque delante del jugador
      _fisicas->crearCuerpo(0,atposX,atposY,atposZ,1,5,0,0,4);
      danyo = 70.0f;
      _motora->getEvent("GolpeGuitarra")->setVolume(0.8f);
      _motora->getEvent("GolpeGuitarra")->start();
    }
    //ATAQUE A DISTANCIA
    else if(strcmp(this->getArma()->getNombre(),"arpa") == 0)
    {
      //Crear cuerpo de colision de ataque delante del jugador
      _fisicas->crearCuerpo(0,atposX,atposY,atposZ,2,2,0.5,1,4);
      danyo = 55.0f;
      _motora->getEvent("Arpa")->setVolume(0.8f);
      _motora->getEvent("Arpa")->start();
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
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    MotorGrafico* _motor = MotorGrafico::GetInstance();
    if(this->getArma() == nullptr){
      _fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      _motor->clearDebug2();
      _motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,2,1,1,2);
    }
    else if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)
    {
      _fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      _motor->clearDebug2();
      _motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,3,1,3,1);
    }
    else if(strcmp(this->getArma()->getNombre(),"arpa") == 0)
    {
      atz += (1.5 * cos(PI * atgy / PIRADIAN));
      atx += (1.5 * sin(PI * atgy / PIRADIAN));
      atposZ += (1.5 * cos(PI * atgy / PIRADIAN));
      atposX += (1.5 * sin(PI * atgy / PIRADIAN));


      _fisicas->updateAtaque(atposX,atposY,atposZ,atgx,atgy,atgz);
      _motor->clearDebug2();
      _motor->dibujarObjetoTemporal(atx,aty,atz,atgx,atgy,atgz,1,1,2,3);
    }

    //Enteros con los enemigos colisionados (atacados)
    vector <unsigned int> atacados = _fisicas->updateArma(atposX,atposY,atposZ);

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
            _motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
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
        //Calcular posiciones si se inicia el ataque especial
        setAnimacion(3);
        if(atackEspTime <= 0)
        {
            animacion = 3;
            atespx = 5 * sin(PI * getRY() / PIRADIAN) + getX();
            atespy = getY();
            atespz = 5 * cos(PI * getRY() / PIRADIAN) + getZ();
            atgx = getRX();
            atgy = getRY();
            atgz = getRZ();
            incrAtDisCirc = 0.0;

            _armaEspecial->setNewPosiciones(atespx, atespy, atespz);
            _armaEspecial->setNewRotacion(getRX(), getRY(), getRZ());

            MotorFisicas* _fisicas = MotorFisicas::getInstance();
            MotorAudioSystem* _motora = MotorAudioSystem::getInstance();

            //Posiciones en el mundo 3D
            _armaEspecial->initPosicionesFisicas(atespx/2, getY()/2, atespz/2);

            //ATAQUE ESPECIAL DEL HEAVY
            if(strcmp(_armaEspecial->getNombre(), NOMBREHEAVY) == 0)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,_armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ(),2,8,1,8,5);
                _motora->getEvent("Arpa")->setVolume(0.8f);
                _motora->getEvent("Arpa")->start();
            }
            //ATAQUE ESPECIAL DE LA BAILAORA
            else if(strcmp(_armaEspecial->getNombre(), NOMBREBAILAORA) == 0)
            {
                //Crear cuerpo de colision de ataque delante del jugador
                _fisicas->crearCuerpo(0,_armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ(),2,8,8,8,5);
                _motora->getEvent("Arpa")->start();
            }
        }

        //Se calcula el danyo del ataque
        aumentosAtaque += por1;
        if(_armaEquipada != NULL)
        {
            aumentosAtaque += (float) _armaEquipada->getAtaque() / por100;// + (float) variacion / 100;
        }
        aumentosAtaque *= 2;
        aumentosAtaque = roundf(aumentosAtaque * por10) / por10;

        //Se lanza un random y si esta dentro de la probabilidad de critico lanza un critico
        int probabilidad = rand() % por100 + 1;
        if(probabilidad <= proAtaCritico)
        {
            critico += (float) danyoCritico / por100;
            critico = roundf(critico * por10) / por10;
        }

        //Se aplican todas las modificaciones en la variable danyo
        danyoF = ataque * critico * aumentosAtaque;
        danyo = roundf(danyoF * por10) / por10;
        barraAtEs = 0;
        return danyo;
    }
    return danyo;
}
/*************** AtacarEspecialUpdate *****************
 *  Funcion que actualiza la posicion y
 *  la colision del ataque especial
 *      Entradas: int danyo
 *      Salidas:
 */
void Jugador::AtacarEspecialUpdate(int*danyo)
{
    MotorGrafico* _motor = MotorGrafico::GetInstance();
    MotorFisicas * _fisicas = MotorFisicas::getInstance();
    Nivel* nivel = Nivel::getInstance();

    //Si el ataque especial es el del Heavy, es cuerpo a cuerpo
    if(strcmp(_armaEspecial->getNombre(), NOMBREHEAVY) == 0)
    {

        //Calculo de la posicion del arma delante  int getAnimacion();del jugador
        atespx = 5 * sin(PI * this->getRY() / PIRADIAN) + this->getX();
        atespz = 5 * cos(PI * this->getRY() / PIRADIAN) + this->getZ();
        _armaEspecial->initPosicionesFisicas(atespx/2, this->getY()/2, atespz/2);
        _armaEspecial->setNewPosiciones(atespx, this->getY(), atespz);
        _armaEspecial->setNewRotacion(getRX(), this->getRY(), getRZ());
    }

    //Si el ataque especial es el de la Bailaora, es circular a distancia
    else if(strcmp(_armaEspecial->getNombre(), NOMBREBAILAORA) == 0)
    {
        //Formula de ataque circular aumentando la distancia
        incrAtDisCirc += 1.5;
        atespz = this->getZ();
        atespz += (incrAtDisCirc * cos(PI * atgy / PIRADIAN));
        atespx = this->getX();
        atespx += (incrAtDisCirc * sin(PI * atgy / PIRADIAN));
        atespposZ = atespz - this->getZ();
        atespposX = atespx - this->getX();
        _armaEspecial->setPosicionesFisicas(atespposZ, 0.0f, atespposZ);

        //Aumento de la rotacion hacia la izquierda.
        atgy += 30;

        if(atgy >= 360.0)
        {
            atgy -= 360.0;
        }
        else if(atgy < 0.0)
        {
            atgy += 360;
        }

        _armaEspecial->setNewPosiciones(atespx, this->getY(), atespz);
        _armaEspecial->setNewRotacion(getRX(), atgy, getRZ());
    }
    //lista de enteros que senyalan a los enemigos atacados
    vector <unsigned int> atacados = _fisicas->updateArmaEspecial(_armaEspecial->getFisX(),_armaEspecial->getFisY(),_armaEspecial->getFisZ());

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
            _motor->colorearEnemigo(255, 0, 255, 55, atacados.at(i));
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
  if(vida < 100)
  {
    vida += can;
    if(vida > 100)vida = 100;
  }
}

void Jugador::AumentarBarraAtEs(int can)
{
  if(barraAtEs < 100)
  {
    barraAtEs += can;
    if(barraAtEs > 100)barraAtEs = 100;
  }
}

void Jugador::AumentarDinero(int can)
{
   dinero += can;
}

void Jugador::Interactuar(int id, int id2)
{

}

/***********AnnadirLlave************
 * Metodo que anade la llave pasada por
 * parametro al vector de llaves que
 * posee el jugador
 * Entradas:
 *          Llave* llave: llave a anadir
 */
void Jugador::AnnadirLlave(Llave* llave)
{
    llaves.push_back(llave);
    cout<<"Llave añadida. Nº de llaves: "<<llaves.size()<<endl;
}

/***********EliminarLlave************
 * Metodo que elimina la llave pasada por
 * parametro del vector de llaves que
 * posee el jugador
 * Entradas:
 *          Llave* llave: llave a eliminar
 */
void Jugador::EliminarLlave(Llave* llave)
{
    unsigned int i = 0;
    bool encontrado = false;
    while(!encontrado)
    {
        i++;
        //Se elimina la llave si coinide con el codigo de la puerta de la llave pasada por parametro
        if(llave->GetCodigoPuerta() == llaves.at(i)->GetCodigoPuerta())
        {
            llaves.erase(llaves.begin() + i);
            encontrado = true;
        }
    }
}

void Jugador::updateInterfaz()
{
    InterfazJugador* interfaz = InterfazJugador::getInstance();
    interfaz->setVida(vida);
    interfaz->setAtaqueEspecial(getBarraAtEs());
    interfaz->setDinero(dinero);
}

bool Jugador::terminaAnimacion()
{
        Times* _tiempo = Times::GetInstance();

        switch(animacion)//comprobamos que la animacion haya terminado
        {
            case 0://andar
                return true;
            case 1://quieto
                return true;
            case 2://ataque
                if(_tiempo->CalcularTiempoPasado(tiempoPasadoAtaque) >= tiempoAtaque || tiempoPasadoAtaque == 0)
                {
                    tiempoPasadoAtaque = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 3://ataque especial
                if(_tiempo->CalcularTiempoPasado(tiempoPasadoAtaEsp) >=  tiempoAtaEsp || tiempoPasadoAtaEsp == 0)
                {
                    tiempoPasadoAtaEsp = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            case 4://coger objeto
                if(_tiempo->CalcularTiempoPasado(tiempoPasadoCogerObjeto) >= tiempoCogerObjeto || tiempoPasadoCogerObjeto == 0)
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

float Jugador::getX()
{
    return posActual.x;
}

float Jugador::getY()
{
    return posActual.y;
}

float Jugador::getZ()
{
    return posActual.z;
}

float Jugador::getNewX()
{
    return posFutura.x;
}

float Jugador::getNewY()
{
    return posFutura.y;
}

float Jugador::getNewZ()
{
    return posFutura.z;
}

float Jugador::getLastX()
{
    return posPasada.x;
}

float Jugador::getLastY()
{
    return posPasada.y;
}

float Jugador::getLastZ()
{
    return posPasada.z;
}

float Jugador::getFisX()
{
    return posFisicas.x;
}

float Jugador::getFisY()
{
    return posFisicas.y;
}

float Jugador::getFisZ()
{
    return posFisicas.z;
}

float Jugador::getRX()
{
    return rotActual.x;
}

float Jugador::getRY()
{
    return rotActual.y;
}

float Jugador::getRZ()
{
    return rotActual.z;
}

//Devuelve la posicion y rotacion del ataque especial
float* Jugador::GetDatosAtEsp()
{
    float* atesp = new float [6];
    atesp[0] = _armaEspecial->getX();
    atesp[1] = _armaEspecial->getY();
    atesp[2] = _armaEspecial->getZ();
    atesp[3] = _armaEspecial->getRX();;
    atesp[4] = _armaEspecial->getRY();;
    atesp[5] = _armaEspecial->getRZ();;

    return atesp;
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

Arma* Jugador::getArma()
{
    return _armaEquipada;
}


Arma* Jugador::getArmaEspecial()
{
    return _armaEspecial;
}

const char* Jugador::getNombre()
{
    return _nombreJugador;
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

int* Jugador::getBuffos()
{
    int* valores = new int[6];
    return valores;
}

float Jugador::getTimeAt()
{
    return atackTime;
}

float Jugador::getLastTimeAt()
{
    return lastAtackTime;
}

float Jugador::getTimeAtEsp()
{
    return atackEspTime;
}

float Jugador::getLastTimeAtEsp()
{
    return lastAtackEspTime;
}

const char*Jugador::getRutaArmaEsp()
{
    return _rutaArmaEspecial;
}

int Jugador::getDinero()
{
    return dinero;
}

int Jugador::getAnimacion()
{
    return animacion;
}

std::vector <Llave*> Jugador::GetLlaves()
{
    return llaves;
}

int Jugador::getID()
{
    return id;
}


void Jugador::setPosiciones(float nx,float ny,float nz)
{
    posActual.x = nx;
    posActual.y = ny;
    posActual.z = nz;
}


void Jugador::setLastPosiciones(float nx,float ny,float nz)
{
    posPasada.x = nx;
    posPasada.y = ny;
    posPasada.z = nz;
}

void Jugador::setRotacion(float nrx, float nry, float nrz)
{
    rotActual.x = nrx;
    rotActual.y = nry;
    rotActual.z = nrz;
}

void Jugador::setNewRotacion(float nrx, float nry, float nrz)
{
    rotateTime = 0.0;
    this->setLastRotacion( rotFutura.x,  rotFutura.y, rotFutura.z);
    rotFutura.x = nrx;
    rotFutura.y = nry;
    rotFutura.z = nrz;
}

void Jugador::setLastRotacion(float nrx, float nry, float nrz)
{
    rotPasada.x = nrx;
    rotPasada.y = nry;
    rotPasada.z = nrz;
}

void Jugador::setNewPosiciones(float nx,float ny,float nz)
{
    moveTime = 0.0;
    this->setLastPosiciones(posFutura.x, posFutura.y, posFutura.z);
    posFutura.x = nx;
    posFutura.y = ny;
    posFutura.z = nz;
}

void Jugador::initPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x = nx;
    posFisicas.y = ny;
    posFisicas.z = nz;
}

void Jugador::setPosicionesFisicas(float nx,float ny,float nz)
{
    posFisicas.x += nx;
    posFisicas.y += ny;
    posFisicas.z += nz;
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

void Jugador::setArma(Arma* arma)
{
    _armaEquipada = arma;
    if(this->getArma() != nullptr)
    {
        if(strcmp(this->getArma()->getNombre(),"guitarra") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            InterfazJugador* interfaz = InterfazJugador::getInstance();
            interfaz->setArma(2);
        }

        if(strcmp(this->getArma()->getNombre(),"arpa") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            InterfazJugador* interfaz = InterfazJugador::getInstance();
            interfaz->setArma(3);
        }

        if(strcmp(this->getArma()->getNombre(),"llave") == 0)//entonces es la guitarra cuerpo a cuerpo
        {
            InterfazJugador* interfaz = InterfazJugador::getInstance();
            interfaz->setArma(1);
        }

        // if(strcmp(this->getArma()->getNombre(),"dinero") == 0)//entonces es la guitarra cuerpo a cuerpo
        // {
        //     InterfazJugador* interfaz = InterfazJugador::getInstance();
        //     dinero = dinero+1;
        //     interfaz->setArma(0);
        // }
    }
    else
    {
        InterfazJugador* interfaz = InterfazJugador::getInstance();
        interfaz->setArma(0);
    }
}


void Jugador::setArmaEspecial(int ataque)
{
    _armaEspecial = new Arma(ataque, _nombreJugador,3,3,3,_rutaArmaEspecial,"");
}

void Jugador::setNombre(const char* nombre)
{
    _nombreJugador = nombre;
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

void Jugador::setTimeAt(float time)
{
    atackTime = time;
}

void Jugador::setLastTimeAt(float time)
{
    lastAtackTime = time;
}


void Jugador::setTimeAtEsp(float time)
{
    atackEspTime = time;
}

void Jugador::setLastTimeAtEsp(float time)
{
    lastAtackEspTime = time;
}


void Jugador::setAnimacion(int est)
{
    Times* _tiempo = Times::GetInstance();

    if(est != animacion)
    {
        //es una nueva animacion
        if(terminaAnimacion())
        {
            animacion = est; //cambiamos la animacion
            switch(animacion)
            {
                case 2:
                    tiempoPasadoAtaque = _tiempo->GetTiempo(1);
                break;
                case 3:
                    tiempoPasadoAtaEsp = _tiempo->GetTiempo(1);
                break;
                case 4:
                    tiempoPasadoCogerObjeto = _tiempo->GetTiempo(1);
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

void Jugador::setID(int nid)
{
    id = nid;
}
