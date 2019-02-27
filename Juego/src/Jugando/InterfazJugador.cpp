#include "InterfazJugador.hpp"

//singleton
InterfazJugador* InterfazJugador::_unica_instancia = 0;
//fin indicador singleton

InterfazJugador::InterfazJugador()
{
    _motor = MotorGrafico::GetInstance();
}

InterfazJugador::~InterfazJugador()
{
    estado = false;
    
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

void InterfazJugador::setArma(int arm)
{
    _motor->SetArma(arm);
}