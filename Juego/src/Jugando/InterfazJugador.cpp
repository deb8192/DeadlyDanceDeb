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
    //_motor->SetArma(1); Esto es la llave que se cambiara de sitio

    if ((arm == constantes.GUITARRA1) || (arm == constantes.GUITARRA2)
        || (arm == constantes.GUITARRA3))
    {
        _motor->SetArma(2);
    }
    else if ((arm == constantes.ARPA1) || (arm == constantes.ARPA2)
        || (arm == constantes.ARPA3))
    {
        _motor->SetArma(3);
    }
    else if ((arm == constantes.FLAUTA1) || (arm == constantes.FLAUTA2)
        || (arm == constantes.FLAUTA3))
    {
        _motor->SetArma(4);
    }
    else // MANO
    {
        _motor->SetArma(0);
    }
}