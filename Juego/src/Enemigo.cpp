#include "Enemigo.hpp"
//#include "Nivel.hpp"
#include "MotorGrafico.hpp"
#include "MotorFisicas.hpp"
#include "MotorAudio.hpp"
#include "times.hpp"

#define PI 3.14159265358979323846
#define PIRADIAN 180.0f

Enemigo::Enemigo()
{

}

Enemigo::~Enemigo(){

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
    /*SenseEventos * eventos = SenseEventos::getInstance();
    //esto es un ejemplo

    
    int * loqueve = eventos->listaObjetos(x,y,z,rotation,20,1,true); //le pedimos al motor de sentidos que nos diga lo que vemos y nos devuelve una lista

    if(loqueve != nullptr)
    {
        if(loqueve[0] == 1)
        {
            std::cout << "ve al jugador" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
        }
    }
    delete loqueve;
    if(rotation < 360)
    {
        rotation += 0.1f;
    }
    else
    {
        rotation = 0.0f;
    }*/



    //esto hay que editarlo para cada llamada segun el arbol de comportamientos puesto que a veces interesara ver ciertas cosas, si se le pasa 1 despues del 20 vera solo al jugador si esta, si es 2 se vera los objetos, si es 3 vera los enemigos(para socorrerlos)

}

Sala* Enemigo::getSala()
{
    return estoy;
}

void Enemigo::setPosiciones(float nx,float ny,float nz)
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

/*************** AtacarEspecial *****************
 *  Funcion que inicia la ejecucion del ataque
 *  especial del enemigo si la barra de ataque
 *  especial esta completa y se pulsa el boton Q /
 *  click derecho del raton.
 *      Entradas:
 *      Salidas: int danyo;
 */
int Enemigo::AtacarEspecial()
{
    float danyoF = 0.f, aumentosAtaque = 0.f, critico = 1.f, por1 = 1.f;
    int danyo = 0, por10 = 10, por100 = 100;
    MotorFisicas* fisicas = MotorFisicas::getInstance();
    MotorAudioSystem* motora = MotorAudioSystem::getInstance();

    cout << vida << " " << barraAtEs << " " << por100 << endl;
    //Se comprueban las restricciones (de momento solo que esta vivo y la barra de ataque especial)
    if(vida > 0 && barraAtEs == por100)
    {
        cout << "ATAQUE ESPECIAL ENEMIGO"<<endl;
        
        //Calcular posiciones si se inicia el ataque especial
        if(atackEspTime <= 0)
        {
            atespx = 6.5 * sin(PI * getRY() / PIRADIAN) + getX();
            atespy = getY();
            atespz = 6.5 * cos(PI * getRY() / PIRADIAN) + getZ();
            atgx = getRX();
            atgy = getRY();
            atgz = getRZ();
            incrAtDisCirc = 0.0;

            //Posiciones en el mundo 3D
            atespposX = (atespx/2);
            atespposY = (getY()/2);
            atespposZ = (atespz/2);

            //Crear cuerpo de colision de ataque delante del jugador
            fisicas->crearCuerpo(0,atespposX,atespposY,atespposZ,2,8,1,8,5);
            motora->getEvent("Bow")->setVolume(0.8f);
            motora->getEvent("Bow")->start();
        }

        //Se calcula el danyo del ataque
        aumentosAtaque += (por1 * 2);
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
        cout << "daño: " <<danyo<<endl;
      
        //Colision
        if(fisicas->IfCollision(fisicas->getEnemiesAtack(),fisicas->getJugador()))
        {
            cout << "Jugador Atacado" << endl;
            danyo = roundf(danyoF * por10) / por10;
        }
        barraAtEs = 0;
        return danyo;
    }
    else
    {
        cout << "No supera las restricciones"<<endl;
        barraAtEs += 1;
    }
    return danyo;
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
        motor->colorearEnemigo(255,0,0,0,enemi);//negro
        tiempoPasadoMuerte = tiempo->getTiempo(1);
    }
    if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) < animacionMuerteTiem){
        if(tiempo->calcularTiempoPasado(tiempoPasadoMuerte) >= 1000.0f){
            motor->colorearEnemigo(255,255,0,0,enemi);//rojo
        }
    }
}

void Enemigo::RecuperarVida(int can)
{

}

void Enemigo::AumentarBarraAtEs(int can)
{
    barraAtEs += can;
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
    barraAtEs = bar;
}

void Enemigo::setAtaque(int ataq)
{
    ataque = ataq;
}

void Enemigo::setArmaEspecial(int ataque)
{
    armaEspecial = new Arma(ataque, "",2,2,2,rutaArmaEspecial,"");
}

void Enemigo::setSuerte(int suer)
{

}

void Enemigo::setDanyoCritico(int danyoC)
{

}

void Enemigo::setProAtaCritico(int probabilidad)
{
    proAtaCritico = probabilidad;
}

void Enemigo::setTimeAtEsp(float time)
{
    atackEspTime = time;
}

void Enemigo::setLastTimeAtEsp(float time)
{
    lastAtackEspTime = time;
}

void Enemigo::setSala(Sala* sala)
{
    estoy = sala;
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
    return barraAtEs;
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

float Enemigo::getTimeAtEsp()
{
    return atackEspTime;
}

float Enemigo::getLastTimeAtEsp()
{
    return lastAtackEspTime;
}