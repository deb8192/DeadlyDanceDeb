#include "Configuracion.hpp"
#include "../Juego.hpp"

Configuracion::Configuracion()
{
    _motor = MotorGrafico::GetInstance();
}

Configuracion::~Configuracion()
{
    // Punteros a clases singleton
    _motor = nullptr;
}

void Configuracion::Iniciar()
{
    _motor->FondoEscena(255,250,200,100);
    _motor->ActivarFuenteDefault();
    _motor->CrearTexto("Configuracion - ESC para salir", 0, 0, 300, 20); // Parametros: texto, x1, y1, x2, y2
}

// Actualiza lo que se ve por pantalla
void Configuracion::Render()
{
    _motor->FondoEscena(255,250,200,100); // Borra
    _motor->RenderEscena();               // Vuelve a pintar
}

void Configuracion::Update()
{
    
}

void Configuracion::ManejarEventos()
{
    if (_motor->EstaPulsado(KEY_ESC)) {
        _motor->ResetKey(KEY_ESC);
        atras();
    }
}

// Vuelve al menu principal
void Configuracion::atras()
{
    _motor->BorrarScena();
    _motor->BorrarGui();
    Juego::GetInstance()->estado.SaltarAlMenu();
}

// Elimina la memoria antes de volver al menu
void Configuracion::Vaciar() {
    cout << "Vaciando config" <<endl;
}