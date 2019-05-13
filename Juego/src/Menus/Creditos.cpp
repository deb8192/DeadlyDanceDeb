#include "Creditos.hpp"
#include "../Juego.hpp"

Creditos::Creditos()
{
    _motor = MotorGrafico::GetInstance();
}

Creditos::~Creditos()
{
    _motor = nullptr;
}

void Creditos::Iniciar()
{  
    _motor->FondoEscena(0,0,0,0);
    _motor->ActivarFuenteDefault();
    _motor->CrearTexto("Creditos - ESC para salir", 0, 0, 300, 20); // Parametros: texto, x1, y1, x2, y2
    _motor->CrearVideo("assets/cinematicas/creditos.avi",0,0,800,600);
}

// Actualiza lo que se ve por pantalla
void Creditos::Render()
{
    _motor->FondoEscena(0,0,0,0);// Borra
    _motor->RenderEscena();// Vuelve a pintar
}

void Creditos::Update()
{
    
}

void Creditos::ManejarEventos()
{
    if (_motor->EstaPulsado(KEY_ESC)) {
        _motor->ResetKey(KEY_ESC);
        atras();
    }
}

// Vuelve al menu principal
void Creditos::atras()
{
    _motor->BorrarScena();
    _motor->BorrarGui();
    Juego::GetInstance()->estado.SaltarAlMenu();
}