#include "Jugador.hpp"

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

Jugador::Jugador()
{

}

Jugador::Jugador(int,int,int,int,int,int)
{
    vida = 100;//esto lo hereda de la interfaz por el protected
    x = 1;
    z = 20;
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
        pz += 10.0*dt;
    }
    if(s)
    {
        az += -50.0;
        az > 1000 ? az = 0 : false;
        pz += -10.0*dt;
    }
    if(a)
    {
        ax += -50.0;
        ax > 1000 ? ax = 0 : false;
        px += -10.0*dt;

    }
    if(d)
    {
        ax += 50.0;
        ax < -1000 ? ax = 0 : false;
        px += 10.0*dt;
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

void Jugador::Atacar(int IDatacante)
{
    cout << "ATAQUE NORMAL" << endl;
    //Colision

    //Buscar en array de enemigos el IDatacado, si se encuentra quitarle vida
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
