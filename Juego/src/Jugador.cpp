#include "Jugador.hpp"
#include "Nivel.hpp"
//#include "MotorGrafico.hpp"
#include <math.h>
#include <stdlib.h>

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

void Jugador::Atacar()
{

}
void Jugador::AtacarEspecial()
{

}

int Jugador::AtacareEspecial()
{  
    bool danya = false, atacado = false;
    float danyoF = 0.0;
    int danyo = 0;
    //SE USARAN MAS VECES ASI QUE CONVENDRIA GENERAR VARIABLES DE INSTANCIA
    //Nivel* nivel = Nivel::getInstance();
    /*MotorGrafico *motor = MotorGrafico::getInstance();
    fisicas = MotorFisicas::getInstance();
    motor->CargarObjetos(x, y, z, rutaArmaEspecial, "");*/
    cout << "Se realiza ataque especial jugador" << endl;
    //int IDenemy = 2;

    //Se comprueban las restricciones (de momento solo que esta vivo y la barra de ataque especial)
    if(vida > 0 && barraAtEs == 100)
    {
        cout << "Supera las restricciones"<<endl;
        //int variacion = rand() % 21 - 10;
        //float aumentosAtaque = 1.0 + (float) ataque / 100;// + (float) variacion / 100;
        /*float aumentosAtaque = roundf(aumentosAtaque * 10) / 10;
        cout << "aumentos " << aumentosAtaque <<endl;*/

        cout << "daño" <<danyo<<endl;
        float critico = 1.0;
        int probabilidad = rand() % 100 + 1;
        if(probabilidad <= proAtaCritico)
        {
            critico += (float) danyoCritico / 100;
            cout<<"critico " << proAtaCritico << " " << critico <<endl;
        }
        danyoF = ataque * critico;
        danyo = roundf(danyoF * 10) / 10;
        cout << "daño" <<danyo<<endl;
        //barraAtEs = 0;
        return danyo;

        /*unsigned int i = 0;
        bool encontrado = false;

        nivel->updateAtEsp();

        //Se comprueba la colision;
        if(danya && !atacado)
        {
            if(nivel->getEnemigos().at(i)->getID() == IDenemy)
            {
                Enemigo * en = nivel->getEnemigos().at(i);
                cout<<"Pupa al " << en->getID();
                en->QuitarVida(danyo);
                cout<<" " << en->getVida()<<endl;
                encontrado = true;
            }
            else
            {
                cout<<"NO daño" << nivel->getEnemigos().at(i)->getID()<<endl;
            }
            i++;
        }

        while(i < nivel->getEnemigos().size() && !encontrado)
        {
            
        }*/
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
    armaEspecial = new Arma(ataque);
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
    return -1;
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