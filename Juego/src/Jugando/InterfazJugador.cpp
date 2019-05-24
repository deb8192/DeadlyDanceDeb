#include "InterfazJugador.hpp"

//singleton
InterfazJugador* InterfazJugador::_unica_instancia = 0;
//fin indicador singleton

InterfazJugador::InterfazJugador()
{
    _motor = MotorGrafico::GetInstance();
    llaveBosActivada = false;
}

InterfazJugador::~InterfazJugador()
{
    estado = false;
    llaveBosActivada = false;
    
    _motor = nullptr;
    delete _unica_instancia;
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

void InterfazJugador::setVida(int vid)
{
    _motor->SetVida(vid);
}

void InterfazJugador::setAtaqueEspecial(int ataq)
{
    _motor->SetBarraEnergia(ataq);
}

void InterfazJugador::setDinero(int din)
{
    _motor->SetDinero(din);
}

void InterfazJugador::setLlaves(int llaves)
{
    if (llaveBosActivada)
    {
        llaves--;
    }
    _motor->SetLlaves(llaves);
}

void InterfazJugador::setArma(int arm)
{
    if (arm == constantes.GUITARRA1)
    {
        _motor->SetArma(2);
    }
    else if (arm == constantes.GUITARRA2)
    {
        _motor->SetArma(3);
    }
    else if (arm == constantes.GUITARRA3)
    {
        _motor->SetArma(4);
    }
    else if (arm == constantes.ARPA1)
    {
        _motor->SetArma(5);
    }
    else if (arm == constantes.ARPA2)
    {
        _motor->SetArma(6);
    }
    else if (arm == constantes.ARPA3)
    {
        _motor->SetArma(7);
    }
    else if (arm == constantes.FLAUTA1)
    {
        _motor->SetArma(8);
    }
    else if (arm == constantes.FLAUTA2)
    {
        _motor->SetArma(9);
    }
    else if (arm == constantes.FLAUTA3)
    {
        _motor->SetArma(10);
    }
    else // MANO
    {
        _motor->SetArma(0);
    }
}

void InterfazJugador::ActivarLlaveBoss()
{
    llaveBosActivada = true;
    _motor->ActivarLlaveBoss();
}