#include "Animacion.hpp"

Animacion::Animacion()
{
    fInicio = 0;//frame incial, donde empieza la animacion
    fFinal = 0;//frame final, donde termina la animacion
    seRepite = true;//se indica si la animacion se repite al terminar
    salto = false;//si al terminar salta a otra animacion se pone a cual animacion salta 
    debeTerminar = false;//por defecto es FALSE, pero si es true hasta que no termina no se puede cambiar de estado
    _salta = nullptr;//animacion a la que salta cuando termina
    velocidad = 1;//velocidad a la que se ejecuta la animacion
}

Animacion::~Animacion()
{
    _salta = nullptr;
}

void Animacion::SetFinal(unsigned int fin)
{
    fFinal = fin;
}

void Animacion::SetInicio(unsigned int ini)
{
    fInicio = ini;
}

void Animacion::SetSalta(bool bo)
{
    salto = bo;
}

void Animacion::SetRepite(bool bo)
{
    seRepite = bo;
}

void Animacion::SetTermina(bool bo)
{
    debeTerminar = bo;
}

void Animacion::SetVelocidad(unsigned int vel)
{
    velocidad = vel;
}

void Animacion::AsignarSiguiente(Animacion * siguien)
{
    _salta = siguien;
}

bool Animacion::GetRepite()
{
    return seRepite;
}

bool Animacion::GetSalta()
{
    return salto;
}

bool Animacion::GetTermina()
{
    return debeTerminar;
}

Animacion * Animacion::GetSiguiente()
{
    return _salta;
}

unsigned int Animacion::GetInicio()
{
    return fInicio;
}

unsigned int Animacion::GetFinal()
{
    return fFinal;
}

unsigned int Animacion::GetVelocidad()
{
    return velocidad;
}