#include "Cinematica.hpp"
#include "../Juego.hpp"

Cinematica::Cinematica()
{
    _motor = MotorGrafico::GetInstance();
}

Cinematica::~Cinematica()
{
    _motor = nullptr;
}

void Cinematica::Iniciar()
{
     // Crear la camara aqui si la necesita  
    _motor->FondoEscena(255,0,0,0);
}

void Cinematica::Render()
{
    _motor->FondoEscena(255,0,0,0);     // Borra
    _motor->RenderEscena();             // Vuelve a pintar
}

void Cinematica::Update()
{
    
}

void Cinematica::ManejarEventos()
{
    // ESC para saltar la cinematica
    if ((_motor->EstaPulsado(KEY_ESC)) ||
        (_motor->EstaPulsado(KEY_ESPACIO))) {
        
        _motor->ResetKey(KEY_ESC);
        Juego::GetInstance()->estado.CambioEstadoMenu();
    }
}

// Elimina la memoria antes de cargar el menu
void Cinematica::Vaciar()
{
    // TO DO: vaciar memoria
    cout << "Vaciando cinematica" <<endl;
}