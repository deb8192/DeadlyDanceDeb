#include "Cinematica.hpp"
#include "../Juego.hpp"

Cinematica::Cinematica()
{
    _motor = MotorGrafico::GetInstance();
    _tiempo = Times::GetInstance();
    tiempoTotal = 16000.5f;
    marcaTiempo = _tiempo->GetTiempo(1);
    tiempoUltimoFrame = 0;
    cambiar = false;
}

Cinematica::~Cinematica()
{
    _motor = nullptr;
    _tiempo = nullptr;
}

void Cinematica::Iniciar()
{
    // Crear la camara aqui si la necesita (TO DO:4 Marzo: No parece que necesite)
    _motor->FondoEscena(255,0,0,0);
}

void Cinematica::Render()
{
    if (!cambiar)
    {
        _motor->FondoEscena(255,0,0,0);     // Borra
        _motor->RenderMotorCinematica(marcaTiempo, tiempoUltimoFrame);
        _motor->RenderEscena();             // Vuelve a pintar
    }
}

void Cinematica::Update()
{
    marcaTiempo = _tiempo->GetTiempo(1);
    tiempoUltimoFrame = _tiempo->CalcularTiempoPasado(marcaTiempo);

    if(( tiempoUltimoFrame >= tiempoTotal) 
        || _motor->finalCinematica())
    {
        CambiarMenu();
    }
}

void Cinematica::ManejarEventos()
{
    // ESC para saltar la cinematica
    if ((_motor->EstaPulsado(KEY_ESC)) ||
        (_motor->EstaPulsado(KEY_ESPACIO))) {
        
        _motor->ResetKey(KEY_ESC);
        _motor->ResetKey(KEY_ESPACIO);
        CambiarMenu();
    }
}

void Cinematica::CambiarMenu()
{
    cambiar = true;
    _motor->BorrarGui();
    Juego::GetInstance()->estado.CambioEstadoMenu();
}