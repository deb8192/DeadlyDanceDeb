#include "InterfazJugador.hpp"

//singleton
InterfazJugador* InterfazJugador::unica_instancia = 0;
//fin indicador singleton

InterfazJugador::InterfazJugador()
{
    vida = 0;//no tiene vida
    ataqueEspecial = 0;//no tiene carga de ataque especial
    dinero = 0;//no tiene dinero
    estado = false;
    arma = 0;// no tiene arma
}

void InterfazJugador::activar()
{
    estado = true;
}

void InterfazJugador::desactivar()
{
    estado = false;
}

bool InterfazJugador::getEstado()
{
    return estado;
}

int * InterfazJugador::getUpdate()
{
    int * datos = new int[5];
    
    if(estado)
    {
        datos[0] = 1;
    }
    else
    {
        datos[0] = 0;
    }

    datos[1] = vida;
    datos[2] = ataqueEspecial;
    datos[3] = dinero;
    datos[4] = arma;

    return datos;//destruirlo en destino
}

void InterfazJugador::setVida(int vid)
{
    if(vid <= 100 && vid >= 0)
    {
        vida = vid;
    }
    else
    {
        if(vid > 100)
            vida = 100;
        if(vid < 0)
            vida = 0;
    }
}

void InterfazJugador::setAtaqueEspecial(int ataq)
{
    if(ataq <= 100 && ataq >= 0)
    {
        ataqueEspecial = ataq;
    }
    else
    {
        if(ataq > 100)
            ataqueEspecial = 100;
        if(ataq < 0)
            ataqueEspecial = 0;
    }
}

void InterfazJugador::setDinero(int din)
{
    if(din <= 9999 && din >= 0)
    {
        dinero = din;
    }
    else
    {
        if(din > 9999)
            dinero = 9999;
        if(din < 0)
            dinero = 0;
    }   
}

void InterfazJugador::setArma(int arm)
{
    arma = arm;
}