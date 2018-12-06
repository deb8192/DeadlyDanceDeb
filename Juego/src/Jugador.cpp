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

float Jugador::getX(){return x;}
float Jugador::getY(){return y;}
float Jugador::getZ(){return z;}
float Jugador::getRX(){return rx;}
float Jugador::getRY(){return ry;}
float Jugador::getRZ(){return rz;}


void Jugador::AtacarEspecial()
{
    cout << "Se realiza ataque especial jugador" << endl;
}

float Jugador::mcd(float ax, float az)
{
    return az ? mcd(az, fmod(ax, az)) : ax;
}

void Jugador::movimiento(float dt,bool a, bool s, bool d, bool w)
{   
    cout << a << s << d << w << endl;
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
    float div = mcd(ax,az);
    
        if(abs(div) != 1.0)
        {    
            ax /= abs(div);
            az /= abs(div);
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